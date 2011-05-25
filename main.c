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
		//event loop
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			//check whether user wants to exit
			if(event.type == SDL_QUIT)
			{
				quit = 1;
			}
			//respond to user resize of window
			if(event.type == SDL_VIDEORESIZE)
			{
				SDL_Surface *screen = sdlStore(NULL,8);
				screen = SDL_SetVideoMode(event.resize.w,event.resize.h,32,SDL_SWSURFACE | SDL_RESIZABLE);
				SDL_Rect *camera = sdlStore(NULL,4);
				camera->w = event.resize.w;
				camera->h = event.resize.h;
			}
			//move player based on mouse movement
			movePlayer(player,event);
		}
		//move player from already gathered data
		movePlayerFromData(player,event);
		//for force reset
		object *objects = objectStore(NULL,2);	
		//move force into velocity, velocity into position
		int i;
		for(i = 0;i < OBJECTS;i++)
		{
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
		//backgroundBlit();
		//blit objects
		blitObject();
		//DEBUG
		object *obj = objectStore(NULL,2);
		SDL_Rect *cam = sdlStore(NULL,4);
		printf("X:%f, Y:%f, CX:%d, CY:%d\n",obj[player].pos.x,obj[player].pos.y,cam->x,cam->y);
		SDL_Delay(100);		
		
	}
	SDL_Quit();
	return 0;
}
