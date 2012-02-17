#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>

#include "header/objectBlit.h"
#include "header/objectStore.h"
#include "header/sdlstore.h"
#include "header/object.h"
#include "header/main.h"
#include "header/blitCircle.h"

int blitObject()
{
	object *obj = objectStore(NULL,GET_OBJECT);
	if(obj == 0)
	{
		puts("DEBUG: blitObject() 2");
		return 1;
	}
	SDL_Rect *camera = sdlStore(NULL,GET_CAMERA);
	if(camera == 0)
	{
		puts("DEBUG: blitObject() 3");
		return 1;
	}
	SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
	if(screen == 0)
	{
		puts("DEBUG: blitObject() 4");
		return 1;
	}
	int player = *(int *)sdlStore(NULL,GET_PLAYER);
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	int i;
	for(i = 0;i < objCount;i++)
	{
		if(obj[i].radius <= 0) continue;
		SDL_Color color = {255,0,0};
		if(i == player)
		{
			color = (SDL_Color){0,0,255};
	 	}
		if(obj[i].radius < obj[player].radius)
		{
			color = (SDL_Color){0,255,0};
		}
		if(blitCircle(obj[i].radius,screen,(SDL_Rect){obj[i].pos.x - camera->x,obj[i].pos.y - camera->y,0,0},color))
		{
			puts("DEBUG: blitObject() 1");
			return 1;
		}
	}
	return 0;
}
