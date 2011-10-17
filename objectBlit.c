#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>

#include "header/objectBlit.h"
#include "header/objectStore.h"
#include "header/sdlstore.h"
#include "header/object.h"
#include "header/main.h"

void blitObject()
{
	object *obj = objectStore(NULL,GET_OBJECT);
	SDL_Rect *camera = sdlStore(NULL,GET_CAMERA);
	SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
	int i;
	for(i = 0;i < OBJECTS;i++)
	{
		if(obj[i].radius <= 0) continue;
		int objX = obj[i].pos.x, objY = obj[i].pos.y;
		int j;
		for(j = 0;j < obj[i].radius;j++)
		{
			unsigned int width = (unsigned int)sqrt(8 * obj[i].radius * j - 4 * j * j);
			int k;
			for(k = 0;k < width;k++)
			{
				SETPIXEL32(screen,objX - camera->x - (width / 2) + k,objY - camera->y - (obj[i].radius - j) + 1,255);
				SETPIXEL32(screen,objX - camera->x - (width / 2) + k,objY - camera->y + (obj[i].radius - j) - 1,255);
			}
		}
	}
	SDL_Flip(screen);
	SDL_FillRect(screen,NULL,0);
}
