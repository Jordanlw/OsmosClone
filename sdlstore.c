#include <SDL/SDL.h>

#include "header/main.h"
#include "header/sdlstore.h"

void *sdlStore(void *data,int option)
{
	static SDL_Surface *screen = 0;
	static SDL_Rect *camera = 0;
	static int player = 0;
	static Uint32 frameTime = 0;
	static struct bgData *background = 0;
	static int *bgSizes = 0;
	static int selObj = 0;
	
	//DEBUG
	//printf("store: %p\n",bgSizes);
	
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
			case SET_FRAMETIME:frameTime = *(Uint32 *)data;break;
			case GET_FRAMETIME:return &frameTime;break;
			case SET_BACKGROUND: background = (struct bgData *)data;break;
			case GET_BACKGROUND: return (void *)background;break;
			case SET_BG_SIZE: bgSizes = (int *)data;break;
			case GET_BG_SIZE: return (void *)bgSizes;break;
			case GET_SELECTED_OBJECT: return (void *)&selObj;break;
			case SET_SELECTED_OBJECT: selObj = *(int *)data;break;
			default: puts("DEBUG: sdlStore() 1"); return (void *)0;break;
		}
	}
	else
	{
		puts("DEBUG: sdlStore() 2");
		return (void *)0;
	}
	//DEBUG
	//printf("selObj %d player %d\n",selObj,player);
	
	return 0;
}
