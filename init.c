#include <stdio.h>
#include <SDL/SDL.h>

#include "header/init.h"
#include "header/objectStore.h"
#include "header/sdlstore.h"
#include "header/collisionDetection.h"
#include "header/random.h"
#include "header/background.h"

#define SIDES_TO_CHECK 4
#define STARTING_OBJECT_SPACING 50
#define STARTING_OBJECT_SPACING_INCREMENT 25

typedef struct _randomSelector
{
	int num;
	int checked;
}randomSelector;

int initBackground()
{
	
	struct bgData *initStorage = malloc(sizeof(struct bgData) * (BG_INIT_W_SIZE / BG_INIT_MAX_SPACING) * 
	(BG_INIT_H_SIZE / BG_INIT_MAX_SPACING) * BG_AMOUNT);
	if(initStorage == 0)
	{
		puts("DEBUG: initBackground() 1");
		return 1;
	}
	sdlStore((void *)initStorage,SET_BACKGROUND);
	int *bgSizes = malloc(sizeof(int) * BG_AMOUNT);
	if(bgSizes == 0)
	{
		puts("DEBUG: initBackground() 1");
		return 1;
	}
	bgSizes[0] = 3;
	bgSizes[1] = 5;
	bgSizes[2] = 7;
	sdlStore((void *)bgSizes,SET_BG_SIZE);
	
	int i;
	for(i = 1;i <= BG_AMOUNT;i++)
	{
		int j;
		for(j = 0;j < BG_INIT_H_SIZE / BG_INIT_MAX_SPACING;j++)
		{
			int k;
			for(k = 0;k < BG_INIT_W_SIZE / BG_INIT_MAX_SPACING;k++)
			{
				int index = ((j * (BG_INIT_W_SIZE / BG_INIT_MAX_SPACING)) + k) * i;
				initStorage[index].pos.x = randomResult(BG_INIT_MAX_SPACING,BG_INIT_MIN_SPACING);
				initStorage[index].pos.x += k * BG_INIT_MAX_SPACING;
				
				initStorage[index].pos.y = randomResult(BG_INIT_MAX_SPACING,BG_INIT_MIN_SPACING);
				initStorage[index].pos.y += j * BG_INIT_MAX_SPACING;
			}
		}
	}
	return 0;
}

void initObjectPosAndSize()
{
	object *obj = objectStore(NULL,GET_OBJECT);
	int player = *(int *)sdlStore(NULL,GET_PLAYER);
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	int i;
	obj[player].radius = STARTING_PLAYER_OBJECT_SIZE;
	obj[player].pos = (vector){LEVEL_WIDTH / 2,LEVEL_HEIGHT / 2};
	//Object being moved
	for(i = 0;i < objCount;i++)
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
				//printf("rand %d, sides left %d num %d\n",randNum,sidesLeft,sides[randNum].num);
				sides[randNum].checked = 1;
				switch(sides[randNum].num)
				{
					case 0: if(obj[k].pos.x + combinedRadius + obj[i].radius < LEVEL_WIDTH)
						    {
						    	newPos = (vector){obj[k].pos.x + combinedRadius, obj[k].pos.y};
						    	//printf("%d selected right of %d\n",i,k);
					    	}; break;
			    	case 1: if(obj[k].pos.x - combinedRadius - obj[i].radius > 0)
			    			{
			    				newPos = (vector){obj[k].pos.x - combinedRadius, obj[k].pos.y};
			    				//printf("%d selected left of %d\n",i,k);
			    			}; break;
	    			case 2: if(obj[k].pos.y + combinedRadius + obj[i].radius < LEVEL_HEIGHT)
	    					{
	    						newPos = (vector){obj[k].pos.x, obj[k].pos.y + combinedRadius};
	    						//printf("%d selected down of %d\n",i,k);
	    					}; break;
					case 3: if(obj[k].pos.y - combinedRadius - obj[i].radius > 0)
							{
								newPos = (vector){obj[k].pos.x, obj[k].pos.y - combinedRadius};
								//printf("%d selected up of %d\n",i,k);
							}; break;
				}
				int j;
				for(j = SIDES_TO_CHECK;j > 0;j--)
				{
					if(sides[j].checked == 0) sides[randNum] = sides[j];
				}
				sidesLeft--;
				//Checking to see whether new found position collides with other objects
				for(j = 0;j < objCount;j++)
				{
					if(isCollidedVectorAndRadius(newPos,obj[j].pos,obj[j].radius + obj[i].radius))
					{
						found = 0;
					}
					//DEBUG
					//printf("r %lu x %f y %f x2 %f y2 %f\n",obj[j].radius + obj[i].radius,newPos.x,newPos.y,obj[j].pos.x,obj[j].pos.y);
				}
				if(found) break;
			}
			/*
			if(found == 1) printf("%d used %d\n",i,k);
			else printf("%d attempted to use %d\n",i,k);
			*/
			/*
			printf("i %d, k %d, run %u, np-x %.0f, np-y %.0f, k-x %.0f, k-y %.0f, cr %lu\n"
			       ,i,k,run,newPos.x,newPos.y,obj[k].pos.x,obj[k].pos.y,combinedRadius);
	        */
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
		/*
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
		*/
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
	sdlStore(camera,SET_CAMERA);
	sdlStore(screen,SET_SCREEN);
	return 0;
}
