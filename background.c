#include <SDL/SDL.h>

#include "header/background.h"
#include "header/sdlstore.h"
#include "header/blitCircle.h"
#include "header/random.h"
#include "header/object.h"
#include "header/objectStore.h"

#define COORDS 2
#define BG_MULT 3

int backgroundBlit(void)
{
	struct PP_Rect *camera = (struct PP_Rect *)sdlStore(NULL,GET_CAMERA);
	if(camera == 0)
	{
		puts("DEBUG: backgroundBlit() 1");
		return -1;
	}
	SDL_Surface *screen = (SDL_Surface *)sdlStore(NULL,GET_SCREEN);
	if(screen == 0)
	{
		puts("DEBUG: backgroundBlit() 2");
		return -1;
	}
	struct bgData *initData = (struct bgData *)sdlStore(NULL,GET_BACKGROUND);
	if(initData == 0)
	{
		puts("DEBUG: backgroundBlit() 3");
		return -1;
	}
	int *bgSizes = (int *)sdlStore(NULL,GET_BG_SIZE);
	if(bgSizes == 0)
	{
		puts("DEBUG: backgroundBlit() 4");
		return -1;
	}
	int bgOffset[BG_AMOUNT][COORDS];
	int i;
	for(i = 0;i < BG_AMOUNT;i++)
	{
		bgOffset[i][0] = ((camera->point.x * BG_MULT) / bgSizes[i]) % camera->size.width;
		bgOffset[i][1] = ((camera->point.y * BG_MULT) / bgSizes[i]) % camera->size.height;
	}
	//DEBUG
	//printf("bg0: x %d y %d cam: x %d y %d\n",bgOffset[0][0],bgOffset[0][1],camera->x,camera->y);
	
	//Iterate over background layers
	for(i = 0;i < BG_AMOUNT;i++)
	{
		//For tiling
		int mw;
		for(mw = 0;mw < (camera->size.width * 2);mw += BG_INIT_W_SIZE)
		{
			int mh;
			for(mh = 0;mh < (camera->size.height * 2);mh += BG_INIT_H_SIZE)
			{
				int k;
				for(k = 0;k < (MIN_INT(BG_INIT_W_SIZE,camera->size.width) * MIN_INT(BG_INIT_H_SIZE,camera->size.height)) / 
				(BG_INIT_MAX_SPACING * BG_INIT_MAX_SPACING);k++)
				{
					int index = k * (i + 1);
					SDL_Rect tmpRect;
					tmpRect.x = initData[index].pos.x + mw - bgOffset[i][0];
					tmpRect.y = initData[index].pos.y + mh - bgOffset[i][1];
					//DEBUG
					//printf("x %5d y %5d w %5d h %5d\n",tmpRect.x,tmpRect.y,tmpRect.w,tmpRect.h);
					
					blitCircle(bgSizes[i],screen,tmpRect,(SDL_Color){255,255,255});
				}
			}
		}
	}
	return 0;
}


