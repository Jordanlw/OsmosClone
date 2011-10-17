#include <SDL/SDL.h>

#include "header/background.h"
#include "header/sdlstore.h"

void backgroundBlit(void)
{
	int amnt = *((int *)sdlStore(NULL,GET_BACKGROUND_AMOUNT));
	SDL_Rect *camera = sdlStore(NULL,GET_CAMERA);
	background *bgs = sdlStore(NULL,GET_BACKGROUND);
	SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
	int i;
	for(i = 0;i < amnt;i++)
	{
		vector pos;
		pos.x = camera->x / bgs[i].divBy;
		pos.y = camera->y / bgs[i].divBy;
		//printf("%f %f\n",pos.x,pos.y);
		while(1)
		{
			//blit
			SDL_Rect rect = {(int)pos.x - camera->x,(int)pos.y - camera->y};
			if(isBgVisible(pos))
			{
				SDL_BlitSurface(bgs[i].img,NULL,screen,&rect);
			}
			//increment position
			pos.x += bgs[i].img->w;
			if(pos.x > camera->x + camera->w)
			{
				pos.x = camera->x / bgs[i].divBy;
				pos.y += bgs[i].img->h;
				if(pos.y > camera->y + camera->h) break;
			}
		}
	}
}

int isBgVisible(vector pos)
{
	SDL_Rect *camera = sdlStore(NULL,GET_CAMERA);
	if((int)pos.x >= camera->x && (int)pos.x <= camera->x + camera->w);
	{
		if((int)pos.y >= camera->y && (int)pos.y <= camera->y + camera->h)
		{
			return 1;
		}
	}
	return 0;
}


