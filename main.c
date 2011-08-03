#include "header/main.h"

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
	sdlStore((void *)&player,64);
	
	if(initObjects())
	{
		puts("DEBUG: main() 2");
		return 1;
	}
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
				SDL_Surface *screen = sdlStore(NULL,8);
				screen = SDL_SetVideoMode(event.resize.w,event.resize.h,32,SDL_SWSURFACE | SDL_RESIZABLE);
				SDL_Rect *camera = sdlStore(NULL,4);
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
		//for force reset
		object *objects = objectStore(NULL,2);	
		//move force into velocity, velocity into position
		int i;
		for(i = 0;i < OBJECTS;i++)
		{
			if(objects[i].radius <= 0) continue;
			velIntoPos(i);
			//if object is outside of boundary, move it inside
			movementBoundCheck(i);
			//reset force
			objects[i].force.x = 0;
			objects[i].force.y = 0;
		}
		//move camera to safe position for blit
		moveCamera(player);
		//blit background onto screen
		backgroundBlit();
		//blit objects
		blitObject();
		//DEBUG
		//SDL_Delay(550);
		//For FPS limit
		Uint32 laterTicks = SDL_GetTicks();
		long delay = (1000 / FPS) - (int)(laterTicks - ticks);
		if(delay > 0) SDL_Delay(delay);
		//store frame time
		unsigned int frameTime = laterTicks - ticks;
		sdlStore((void *)&frameTime,SETFRAMETIME);
	}
	SDL_Quit();
	return 0;
}
