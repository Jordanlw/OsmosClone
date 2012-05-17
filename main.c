#include <stdio.h>
#include <unistd.h>
#include <ppapi/c/ppb_core.h>
#include <ppapi/c/pp_time.h>
#include <ppapi/c/pp_completion_callback.h>
#include <ppapi/c/ppb_graphics_2d.h>

#include "header/main.h"
#include "header/init.h"
#include "header/sdlstore.h"
#include "header/playermovement.h"
#include "header/velIntoPos.h"
#include "header/movementBoundCheck.h"
#include "header/mergeOverlapped.h"
#include "header/background.h"
#include "header/objectBlit.h"
#include "header/objectStore.h"
#include "header/aimovement.h"
#include "header/debug.h"
#include "header/blit.h"
#include "header/nullCallbacks.h"

void *gameMain(void *data)
{
	//DEBUG
	puts("DEBUG: entered gameMain().");
	
	//Initiate SDL
	if(initGame())
	{
		puts("DEBUG: main() 1");
		return (void *)1;
	}
	//DEBUG
	puts("DEBUG: past initGame().");
	
	//Initiate SDL_TTF
	/*
	if(TTF_Init())
	{
		puts("DEBUG: main() 6");
		return 1;
	}
	*/
	//used for multiplayer and also ease of passing data
	int player = 0;
	sdlStore((void *)&player,GET_PLAYER);
	if(initObjects())
	{
		puts("DEBUG: main() 2");
		return 1;
	}
	//DEBUG
	puts("DEBUG: past initObjects().");
	
	initObjectPosAndSize();
	if(initBackground())
	{
		puts("DEBUG: main() 4");
		return 1;
	}
	//DEBUG
	puts("DEBUG: past initBackground().");
	
	//game loop
	//int quit = 0;
	//if set, run through game changing functions only when n is pressed
	int pauseStep = 0;//INIT_PAUSE;
	//Make available the GetTimeTicks function
	PPB_Core *coreInterface = sdlStore(NULL,GET_CORE_INTERFACE);
	while(1/*!quit*/)
	{
		//For FPS limit
		PP_TimeTicks ticks = coreInterface->GetTimeTicks() * 1000;
		//event loop
		//SDL_Event event;
		//if set, allow a game changing frame to happen
		int nextStep = 0;
		//Store left arrow or right arrow pressed state
		int keyboardArrow = 0;
		/*
		while(SDL_PollEvent(&event))
		{
			//DEBUG
			if(event.type == SDL_VIDEORESIZE)
			{
				puts("RESIZE");
			}
			
			switch(event.type)
			{
				//Respond to user exiting the game
				/*
				case SDL_QUIT: quit = 1; break;
				*/
				//Respond to window being resized by user
				/*
				case SDL_VIDEORESIZE:
				{
					SDL_Surface *screen = (SDL_Surface *)sdlStore(NULL,GET_SCREEN);
					screen = SDL_SetVideoMode(event.resize.w,event.resize.h,32,SDL_SWSURFACE | SDL_RESIZABLE);
					screen = screen;
					SDL_Rect *camera = (SDL_Rect *)sdlStore(NULL,GET_CAMERA);
					camera->w = event.resize.w;
					camera->h = event.resize.h;
					//DEBUG
					//printf("resize: w %d h %d\n",camera->w,camera->h);
					//printf("video: event %d\n",event.type);
				}
				break;
				//Move player base on mouse position and mouse button activity
				case SDL_MOUSEBUTTONDOWN:
					;
				case SDL_MOUSEBUTTONUP:
					//DEBUG
					//printf("mouse: event %d down %d up %d\n",event.type,SDL_MOUSEBUTTONDOWN,SDL_MOUSEBUTTONUP);
					
					movePlayer(event);
					break;
				//Respond to key presses
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_n: nextStep = 1; break;
						case SDLK_p: 
							if(pauseStep) pauseStep = 0;
							else pauseStep = 1;
							break;
						case SDLK_LEFT:
							keyboardArrow = KEYBOARD_LEFT;
							break;
						case SDLK_RIGHT:
							keyboardArrow = KEYBOARD_RIGHT;
							break;
						default: break;
					}
					//DEBUG
					//printf("keydown: event %d\n",event.type);
					
					break;
				default: 
					//DEBUG
					//printf("default: event %d\n",event.type);
					break;
			}
		}
		*/
		if(!pauseStep || nextStep)
		{
			//move player from already gathered data
			movePlayerFromData(player);
			//find target, apply force towards target
			moveAiObjects();
			//move force into velocity, velocity into position
			velIntoPos();
			//if object is outside of boundary, move it inside
			movementBoundCheck();
			//merge objects together when overlapped
			mergeOverlapped();
			//if object is outside of boundary, move it inside
			movementBoundCheck();
		}
		updateSelectedObj(keyboardArrow);
		//move camera to safe position for blit
		moveCamera();
		//debugCall(DEBUG_CALL_BEFORE_BLIT);
		//blit background onto screen
		if(backgroundBlit())
		{
			puts("DEBUG: main() 5");
			return (void *)1;
		}
		//blit objects
		if(blitObject())
		{
			puts("DEBUG: main() 3");
			return (void *)1;
		}
		//blit inital unpause screen
		/*
		if(pauseStep == INIT_PAUSE)
		{
			if(blitPause())
			{
				puts("DEBUG: main() 7");
				return 1;
			}
		}
		*/
		//flip and erase screen
		PP_Resource screen = (PP_Resource)sdlStore(NULL,GET_SCREEN);
		PPB_Graphics2D *g2DInterface = (PPB_Graphics2D *)sdlStore(NULL,GET_2D_INTERFACE);
		struct PP_CompletionCallback callback = {nullCallback,NULL,0};
		g2DInterface->Flush(screen,callback);
		//SDL_FillRect(screen,NULL,0);
		
		//For FPS limit
		long delay = (1000 / FPS) - ((coreInterface->GetTimeTicks() * 1000) - ticks);
		if(delay > 0) usleep(delay * 1000);
		//store frame time
		unsigned int frameTime = (coreInterface->GetTimeTicks() * 1000) - ticks;
		sdlStore((void *)&frameTime,SET_FRAMETIME);
	}
	return (void *)0;
}
