#include <SDL/SDL.h>

#include "header/main.h"
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
			case SET_CAMERA:camera = (SDL_Rect *)data;break;
			case SET_SCREEN:screen = (SDL_Surface *)data;break;
			case GET_CAMERA:return (void *)camera;break;
			case GET_SCREEN:return (void *)screen;break;
			case SET_PLAYER:player = *(int *)data;break;
			case GET_PLAYER:return (void *)&player;break;
			case SET_BACKGROUND:backgrounds = (background *)data;break;
			case GET_BACKGROUND:return (void *)backgrounds;break;
			case SET_BACKGROUND_AMOUNT:amntBackgrounds = (long)data;break;
			case GET_BACKGROUND_AMOUNT:return &amntBackgrounds;break;
			case SET_FRAMETIME:frameTime = *(Uint32 *)data;break;
			case GET_FRAMETIME:return &frameTime;break;
			default:break;
		}
	}
	return 0;
}
