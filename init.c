#include <stdio.h>
#include <SDL/SDL.h>

#include "header/init.h"
#include "header/objectStore.h"
#include "header/sdlstore.h"
#include "header/collisionDetection.h"
#include "header/random.h"
#include "header/main.h"
#include "header/background.h"

#define SIDES_TO_CHECK 4
#define STARTING_OBJECT_SPACING 10
#define STARTING_OBJECT_SPACING_INCREMENT 25

typedef struct _randomSelector
{
	int num;
	int checked;
}randomSelector;

void initObjectPosAndSize()
{
	object *obj = objectStore(NULL,GETOBJECT);
	int player = *(int *)sdlStore(NULL,GETPLAYER);
	int i;
	obj[player].radius = STARTING_PLAYER_OBJECT_SIZE;
	obj[player].pos = (vector){LEVEL_WIDTH / 2,LEVEL_HEIGHT / 2};
	//Object being moved
	for(i = 0;i < OBJECTS;i++)
	{
		if(i == player) continue;
		obj[i].radius = randomResult(MAX_OBJECT_SIZE,MIN_OBJECT_SIZE);
		unsigned int run = 0, found = 0;
		vector newPos;
		unsigned long combinedRadius;
		int k;
		//Object who's position is being used to find new object position
		for(k = 0;;k++)
		{
			if(k >= i) k = 0, run++;
			if(k == i || obj[k].radius == 0) continue;
			if(run == 0) combinedRadius = obj[k].radius + obj[i].radius + STARTING_OBJECT_SPACING;
			else combinedRadius = obj[k].radius + obj[i].radius + STARTING_OBJECT_SPACING + (STARTING_OBJECT_SPACING_INCREMENT * run);
			found = 1;
			int m;
			randomSelector sides[SIDES_TO_CHECK];
			int sidesLeft = SIDES_TO_CHECK - 1;
			for(m = 0;m < SIDES_TO_CHECK;m++) sides[m].num = m, sides[m].checked = 0;
			//Cycle through new positions
			for(m = 0;m < SIDES_TO_CHECK;m++)
			{
				int randNum = randomResult(sidesLeft,0);
				printf("rand %d, sides left %d num %d\n",randNum,sidesLeft,sides[randNum].num);
				sides[randNum].checked = 1;
				switch(sides[randNum].num)
				{
					case 0: if(obj[k].pos.x + combinedRadius + obj[i].radius < LEVEL_WIDTH)
						    {
						    	newPos = (vector){obj[k].pos.x + combinedRadius, obj[k].pos.y};
						    	printf("%d selected right of %d\n",i,k);
					    	}; break;
			    	case 1: if(obj[k].pos.x - combinedRadius - obj[i].radius > 0)
			    			{
			    				newPos = (vector){obj[k].pos.x - combinedRadius, obj[k].pos.y};
			    				printf("%d selected left of %d\n",i,k);
			    			}; break;
	    			case 2: if(obj[k].pos.y + combinedRadius + obj[i].radius < LEVEL_HEIGHT)
	    					{
	    						newPos = (vector){obj[k].pos.x, obj[k].pos.y + combinedRadius};
	    						printf("%d selected down of %d\n",i,k);
	    					}; break;
					case 3: if(obj[k].pos.y - combinedRadius - obj[i].radius > 0)
							{
								newPos = (vector){obj[k].pos.x, obj[k].pos.y - combinedRadius};
								printf("%d selected up of %d\n",i,k);
							}; break;
				}
				int j;
				for(j = SIDES_TO_CHECK;j > 0;j--)
				{
					if(sides[j].checked == 0) sides[randNum] = sides[j];
				}
				sidesLeft--;
				//Checking to see whether new found position collides with other objects
				for(j = 0;j < OBJECTS;j++)
				{
					if(isCollidedVectorAndRadius(newPos,obj[j].pos,obj[j].radius + obj[i].radius)) found = 0;
				}
				if(found) break;
			}
			if(found == 1) printf("%d used %d\n",i,k);
			else printf("%d attempted to use %d\n",i,k);
			printf("i %d, k %d, run %u, np-x %.0f, np-y %.0f, k-x %.0f, k-y %.0f, cr %lu\n"
			       ,i,k,run,newPos.x,newPos.y,obj[k].pos.x,obj[k].pos.y,combinedRadius);
	        if(found) break;
		}
		if(found == 1)
		{	
			/*
			printf("FOUND - i %d\n",i);
			printf("np-x %.0f, np-y %.0f\n",newPos.x,newPos.y);
			*/
			obj[i].pos = newPos;
		}
		//DEBUG
		int m;
		for(m = 0;m < OBJECTS;m++)
		{
			if(i == m) continue;
			if(isCollidedVectorAndRadius(newPos,obj[m].pos,obj[i].radius + obj[m].radius))
			{
				printf("%d is colliding with %d\n",i,m);
			}
		}
		if(found == 0) printf("nothing found for %d\n",i);
		puts("");
	}
}

int initSDL()
{
	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		puts("DEBUG: initSDL() 1");
		return 1;
	}
	SDL_Rect *camera = malloc(sizeof(SDL_Rect));
	camera->x = 0;
	camera->y = 0;
	camera->w = DEFAULT_WIDTH;
	camera->h = DEFAULT_HEIGHT;
	SDL_Surface *screen = SDL_SetVideoMode(camera->w,camera->h,32,SDL_SWSURFACE | SDL_RESIZABLE);
	if(!screen)
	{
		puts("DEBUG: initSDL() 2");
		return 1;
	}
	sdlStore(camera,1);
	sdlStore(screen,2);
	if(initBackground())
	{
		puts("DEBUG: initSDL() 3");
		return 1;
	}
	return 0;
}

int initBackground()
{
	DIR *directory = opendir(".");
	if(!isFileExist(directory,"resource"))
	{
		puts("DEBUG: initBackground() 1");
		return 1;
	}
	directory = opendir("resource");
	long amount = 0;
	int init = BG_INIT_SIZE;
	background *bgs = malloc(sizeof(background) * init);
	if(!bgs)
	{
		puts("DEBUG: initBackground() 2");
		return 1;
	}
	struct dirent *entry;
	for(entry = readdir(directory);entry != NULL;entry = readdir(directory))
	{
		if(!strncmp(entry->d_name,"bg",2))
		{
			int len = strlen("resource");
			int lenE = strlen(entry->d_name);
			char new[len+lenE+1];
			sprintf(new,"%s%s","resource/",entry->d_name);
			bgs[amount].img = SDL_LoadBMP(new);
			if(SDL_SetColorKey(bgs[amount].img,SDL_SRCCOLORKEY,SDL_MapRGB(bgs[amount].img->format,0,255,0)))
			{
				puts("DEBUG: initBackground() 6");
				return 1;
			}
			if(!bgs[amount].img)
			{
				puts("DEBUG: initBackground() 5");
				return 1;
			}
			bgs[amount].divBy = findNumber(entry->d_name) + 1;
			amount++;
			if(amount >= init)
			{
				background *tmp = realloc(bgs,sizeof(background) * init * 2);
				if(!tmp)
				{
					puts("DEBUG: initBackground() 4");
					return 1;
				}
				if(tmp != bgs) free(bgs);
				bgs = tmp;
				init *= 2;
			}
		}
	}
	if(amount < init)
	{
		background *tmp = bgs;
		tmp = realloc(bgs,amount * sizeof(background));
		if(!tmp) 
		{
			puts("DEBUG: initBackground() 3");
		 	return 1;
	 	}
		bgs = tmp;
	}
	sdlStore((void *)bgs,256);
	sdlStore((void *)amount,2048);
	return 0;
}

int findNumber(const char *string)
{
	char copy[5000];
	strncpy(copy,string,sizeof(copy));
	int i = strlen(copy);
	for(;copy[i] < '0' || copy[i] > '9';i--);
	i++;
	copy[i] = '\0';
	for(i = 0;copy[i] < '0' || copy[i] > '9';i++);
	char tmp[5000];
	strncpy(tmp,copy + i,sizeof(tmp));
	return atoi(tmp);
}

int isFileExist(DIR *directory,const char *file)
{
	struct dirent *entry;
	do
	{
		entry = readdir(directory);
		if(!strcmp(file,entry->d_name))
		{
			return 1;
		}
	}while(entry != NULL);
	return 0;
}
