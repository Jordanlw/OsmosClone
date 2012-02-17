#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

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

int main(int argc,char **args)
{
	//Initiate SDL
	if(initSDL())
	{
		puts("DEBUG: main() 1");
		return 1;
	}
	//Initiate SDL_TTF
	if(TTF_Init())
	{
		puts("DEBUG: main() 6");
		return 1;
	}
	//used for multiplayer and also ease of passing data
	int player = 0;
	sdlStore((void *)&player,GET_PLAYER);
	if(initObjects())
	{
		puts("DEBUG: main() 2");
		return 1;
	}
	initObjectPosAndSize();
	if(initBackground())
	{
		puts("DEBUG: main() 4");
		return 1;
	}
	//game loop
	int quit = 0;
	//if set, run through game changing functions only when n is pressed
	int pauseStep = INIT_PAUSE;
	while(!quit)
	{
		//For FPS limit
		Uint32 ticks = SDL_GetTicks();
		//event loop
		SDL_Event event;
		//if set, allow a game changing frame to happen
		int nextStep = 0;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				//Respond to user exiting the game
				case SDL_QUIT: quit = 1; break;
				//Respond to window being resized by user
				case SDL_VIDEORESIZE:
				{
					SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
					screen = SDL_SetVideoMode(event.resize.w,event.resize.h,32,SDL_SWSURFACE | SDL_RESIZABLE);
					screen = screen;
					SDL_Rect *camera = sdlStore(NULL,GET_CAMERA);
					camera->w = event.resize.w;
					camera->h = event.resize.h;
					//DEBUG
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
		if(!pauseStep || nextStep)
		{
			//move player from already gathered data
			movePlayerFromData(player,event);
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
			//move camera to safe position for blit
		}
		moveCamera(player);
		//debugCall(DEBUG_CALL_BEFORE_BLIT);
		//blit background onto screen
		if(backgroundBlit())
		{
			puts("DEBUG: main() 5");
			return 1;
		}
		//blit objects
		if(blitObject())
		{
			puts("DEBUG: main() 3");
			return 1;
		}
		//blit inital unpause screen
		if(pauseStep == INIT_PAUSE)
		{
			if(blitPause())
			{
				puts("DEBUG: main() 7");
				return 1;
			}
		}
		//flip and erase screen
		SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
		SDL_Flip(screen);
		SDL_FillRect(screen,NULL,0);
		
		//For FPS limit
		long delay = (1000 / FPS) - (int)(SDL_GetTicks() - ticks);
		if(delay > 0) SDL_Delay(delay);
		//store frame time
		unsigned int frameTime = SDL_GetTicks() - ticks;
		sdlStore((void *)&frameTime,SET_FRAMETIME);
	}
	SDL_Quit();
	return 0;
}
