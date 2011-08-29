#include <SDL/SDL.h>

#include "header/background.h"
#include "header/sdlstore.h"

void *sdlStore(void *data,int option)
{
	static SDL_Surface *screen = 0;
	static SDL_Rect *camera = 0;
	static int player = 0;
	static background *backgrounds = 0;
	static int amntBackgrounds = 0;
	static Uint32 frameTime = 0;
	
	if(option)
	{
		switch(option)
		{
			case 1:camera = (SDL_Rect *)data;break;
			case 2:screen = (SDL_Surface *)data;break;
			case 4:return (void *)camera;break;
			case 8:return (void *)screen;break;
			case 64:player = *(int *)data;break;
			case 128:return (void *)&player;break;
			case 256:backgrounds = (background *)data;break;
			case 1024:return (void *)backgrounds;break;
			case 2048:amntBackgrounds = (long)data;break;
			case 4096:return &amntBackgrounds;break;
			case 3:frameTime = *(Uint32 *)data;break;
			case 5:return &frameTime;break;
			default:break;
		}
	}
	return 0;
}
