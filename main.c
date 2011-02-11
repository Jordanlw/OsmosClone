#include "header/main.h"

int main(int argc,char **args)
{
	//Initate SDL
	if(initSDL())
	{
		puts("DEBUG: main() 1");
		return 1;
	}
	
	//can be replaced with more advance multiplayer
	int player = 1;
	
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
				SDL_Screen *screen = sdlStore(NULL,8);
				screen = SDL_SetVideoMode(event.resize.w,event.resize.h,32,SDL_SWSURFACE | SDL_RESIZABLE);
				SDL_Rect *camera = sdlStore(NULL,4);
				camera->w = event.resize.w;
				camera->h = event.resize.h;
			}
			movePlayer(player,event);
		}
		
	}
}
