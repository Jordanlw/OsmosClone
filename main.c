#include <stdio.h>
#include <SDL/SDL.h>

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

int main(int argc,char **args)
{
	//Initate SDL
	if(initSDL())
	{
		puts("DEBUG: main() 1");
		return 1;
	}
	//used for multiplayer and also ease of passing data
	int player = 0;
	sdlStore((void *)&player,GETPLAYER);
	
	if(initObjects())
	{
		puts("DEBUG: main() 2");
		return 1;
	}
	initObjectPosAndSize();
	//game loop
	int quit = 0;
	while(!quit)
	{
		//For FPS limit
		Uint32 ticks = SDL_GetTicks();
		//event loop
		int eventRun = 0;
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			//check whether user wants to exit
			if(event.type == SDL_QUIT)
			{
				quit = 1;
			}
			//respond to user resize of window
			else if(event.type == SDL_VIDEORESIZE)
			{
				SDL_Surface *screen = sdlStore(NULL,GETSCREEN);
				screen = SDL_SetVideoMode(event.resize.w,event.resize.h,32,SDL_SWSURFACE | SDL_RESIZABLE);
				screen = screen;
				SDL_Rect *camera = sdlStore(NULL,GETCAMERA);
				camera->w = event.resize.w;
				camera->h = event.resize.h;
			}
			//move player based on mouse movement
			else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				movePlayer(eventRun,event);
				eventRun++;
			}
		}
		eventRun = 0;
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
		//Move overlapped objects
		//Not needed, merging prevents need for underOverlapping
		//underOverlap();
		//if object is outside of boundary, move it inside
		movementBoundCheck();
		//move camera to safe position for blit
		moveCamera(player);
		//blit background onto screen
		backgroundBlit();
		//blit objects
		blitObject();
		
		//For FPS limit
		long delay = (1000 / FPS) - (int)(SDL_GetTicks() - ticks);
		if(delay > 0) SDL_Delay(delay);
		//store frame time
		unsigned int frameTime = SDL_GetTicks() - ticks;
		sdlStore((void *)&frameTime,SETFRAMETIME);
	}
	SDL_Quit();
	return 0;
}
