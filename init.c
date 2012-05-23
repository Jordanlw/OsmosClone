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
#include "header/sdlstore.h"
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
	sdlStore((void *)initStorage,SET_BACKGROUND);
	int *bgSizes = (int *)malloc(sizeof(int) * BG_AMOUNT);
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
	object *obj = (object *)objectStore(NULL,GET_OBJECT);
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

int initGame()
{
	//DEBUG
	puts("DEBUG: initGame() - entered");
	
	while(sdlStore(NULL,GET_PAST_DID_CREATE) == 0)
	{
		usleep(1);
	}
	//DEBUG
	puts("DEBUG: initGame() - checkpoint 1");
	
	PP_Instance instance = *(PP_Instance *)sdlStore(NULL,GET_NACL_INSTANCE);
	PPB_Graphics2D *g2DInterface = (PPB_Graphics2D *)sdlStore(NULL,GET_2D_INTERFACE);
	PPB_Instance *instanceInterface = (PPB_Instance *)sdlStore(NULL,GET_INSTANCE_INTERFACE);
	PPB_ImageData *imageInterface = (PPB_ImageData *)sdlStore(NULL,GET_IMAGE_INTERFACE);
	PPB_InputEvent *inputInterface = (PPB_InputEvent *)sdlStore(NULL,GET_INPUT_INTERFACE);
	PPB_Core *coreInterface = (PPB_Core *)sdlStore(NULL,GET_CORE_INTERFACE);
	//DEBUG
	puts("DEBUG: initGame() - checkpoint 2");
	
	sem_t *sem = malloc(sizeof(sem_t));
	sem_init(sem,0,0);
	struct inputCallbackData *callbackInputData = malloc(sizeof(struct inputCallbackData));
	*callbackInputData = (struct inputCallbackData){instance,PP_INPUTEVENT_CLASS_MOUSE,sem};
	coreInterface->CallOnMainThread(0,PP_MakeOptionalCompletionCallback(inputCallback,(void *)callbackInputData),0);
	sem_wait(sem);
	free(callbackInputData);
	callbackInputData = 0;
	//DEBUG
	puts("DEBUG: initGame() - checkpoint 3");
	
	struct PP_Rect *camera = (struct PP_Rect *)malloc(sizeof(struct PP_Rect));
	*camera = (struct PP_Rect){{0,0},{DEFAULT_WIDTH,DEFAULT_HEIGHT}};
	struct g2DCallbackData *callbackg2DData = malloc(sizeof(struct g2DCallbackData));
	*callbackg2DData = (struct g2DCallbackData){instance,&(struct PP_Size){camera->size.width,camera->size.height},PP_TRUE,sem};
	coreInterface->CallOnMainThread(0,PP_MakeOptionalCompletionCallback(g2DCallback,(void *)callbackg2DData),0);
	sem_wait(sem);
	free(callbackg2DData);
	callbackg2DData = 0;
	//DEBUG
	puts("DEBUG: initGame() - checkpoint 4");
	
	PP_Resource screen = *(PP_Resource *)sdlStore(NULL,GET_SCREEN);
	struct bindCallbackData *callbackBindData = malloc(sizeof(struct bindCallbackData));
	*callbackBindData = (struct bindCallbackData){instance,screen,sem};
	coreInterface->CallOnMainThread(0,PP_MakeOptionalCompletionCallback(bindCallback,(void *)callbackBindData),0);
	sem_wait(sem);
	free(callbackBindData);
	callbackBindData = 0;
	
	void *pixels = imageInterface->Map(screen);
	struct PP_Point *mousePos = malloc(sizeof(struct PP_Point));
	
	sdlStore((void *)mousePos,SET_MOUSE_POS);
	int player = *(int *)sdlStore(NULL,GET_PLAYER);
	sdlStore((void *)&player,SET_SELECTED_OBJECT);
	sdlStore(camera,SET_CAMERA);
	//DEBUG
	puts("DEBUG: initGame() - left");
	
	return 0;
}
