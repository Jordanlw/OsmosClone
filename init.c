#include <stdio.h>
#include <ppapi/c/pp_instance.h>
#include <ppapi/c/pp_bool.h>
#include <ppapi/c/ppb_graphics_2d.h>
#include <ppapi/c/pp_size.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppb_image_data.h>
#include <ppapi/c/ppb_input_event.h>
#include <ppapi/c/pp_point.h>
#include <ppapi/c/pp_rect.h>
#include <ppapi/c/pp_errors.h>
#include <ppapi/c/ppb_core.h>
#include <ppapi/c/pp_completion_callback.h>

#include "header/init.h"
#include "header/objectStore.h"
#include "header/store.h"
#include "header/collisionDetection.h"
#include "header/random.h"
#include "header/background.h"
#include "header/callbacks.h"

#define SIDES_TO_CHECK 4
#define STARTING_OBJECT_SPACING 100
#define STARTING_OBJECT_SPACING_INCREMENT 25

typedef struct _randomSelector
{
	int num;
	int checked;
}randomSelector;

int initBackground()
{
	
	struct bgData *initStorage = (struct bgData *)malloc(sizeof(struct bgData) * (BG_INIT_W_SIZE / BG_INIT_MAX_SPACING) * \
	(BG_INIT_H_SIZE / BG_INIT_MAX_SPACING) * BG_AMOUNT);
	if(initStorage == 0)
	{
		puts("DEBUG: initBackground() 1");
		return 1;
	}
	struct store *stored = GET_STORE();
	stored->background = initStorage;
	int *bgSizes = (int *)malloc(sizeof(int) * BG_AMOUNT);
	if(bgSizes == 0)
	{
		puts("DEBUG: initBackground() 1");
		return 1;
	}
	bgSizes[0] = 3;
	bgSizes[1] = 5;
	bgSizes[2] = 7;
	stored->bgSizes = bgSizes;
	
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
	struct store *stored = GET_STORE();
	object *obj = (object *)objectStore(NULL,GET_OBJECT);
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	int i;
	obj[stored->player].radius = STARTING_PLAYER_OBJECT_SIZE;
	obj[stored->player].pos = (vector){LEVEL_WIDTH / 2,LEVEL_HEIGHT / 2};
	//Object being moved
	for(i = 0;i < objCount;i++)
	{
		if(i == stored->player) continue;
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

int initGame()
{
	//DEBUG
	puts("DEBUG: initGame() - entered");
	
	struct store *stored = GET_STORE();
	while(stored->didCreate == 0)
	{
		usleep(1);
	}
	//DEBUG
	puts("DEBUG: initGame() - checkpoint 1");
	
	CALL_ON_MAIN_THREAD(inputCallback,stored->coreInterface,struct inputCallbackData,stored->instance,PP_INPUTEVENT_CLASS_MOUSE);
	//DEBUG
	puts("DEBUG: initGame() - checkpoint 3");

	CALL_ON_MAIN_THREAD(g2DCallback,stored->coreInterface,struct g2DCallbackData,stored->instance,DEFAULT_WIDTH,DEFAULT_HEIGHT,PP_TRUE);
	//DEBUG
	puts("DEBUG: initGame() - checkpoint 4");
	
	CALL_ON_MAIN_THREAD(bindCallback,stored->coreInterface,struct bindCallbackData,stored->instance,stored->screen);
	//DEBUG
	puts("DEBUG: initGame() - checkpoint 5");
	
	CALL_ON_MAIN_THREAD(imageCallback,stored->coreInterface,struct imageCallbackData,stored->instance,(struct PP_Size){DEFAULT_WIDTH,DEFAULT_HEIGHT},0);
	
	CALL_ON_MAIN_THREAD(mapCallback,stored->coreInterface,struct mapCallbackData,stored->image);
	//DEBUG
	puts("DEBUG: initGame() - checkpoint 6");
	
	stored->selObj = stored->player;
	stored->camera = (struct PP_Rect){{0,0},{DEFAULT_WIDTH,DEFAULT_HEIGHT}};
	//DEBUG
	puts("DEBUG: initGame() - left");
	
	return 0;
}
