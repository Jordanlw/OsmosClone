#include <SDL/SDL.h>

#include "header/background.h"
#include "header/sdlstore.h"
#include "header/blitCircle.h"
#include "header/random.h"

#define GET_INIT_DATA(x,y,layer,array) (array[(((y) * ((BG_INIT_W_SIZE) / (BG_INIT_MAX_SPACING)) + (x)) * (layer))])

void backgroundBlit(void)
{
	SDL_Rect *camera = sdlStore(NULL,GET_CAMERA);
	SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
	bgData *initData = sdlStore(NULL,GET_BACKGROUND);
	int *bgSizes = (int *)sdlStore(NULL,GET_BG_SIZE);
	//printf("bg: %p\n",bgSizes);
	//Iterate over background layers
	int i;
	for(i = 1;i <= BG_AMOUNT;i++)
	{
		int j;
		for(j = 0;j < (MIN_INT(BG_INIT_H_SIZE,camera->h) / BG_INIT_MAX_SPACING);j++)
		{
			int k;
			for(k = 0;k < (MIN_INT(BG_INIT_W_SIZE,camera->w) / BG_INIT_MAX_SPACING);k++)
			{
				SDL_Rect tmpRect = (SDL_Rect){GET_INIT_DATA(k,j,i,initData).pos.x,GET_INIT_DATA(k,j,i,initData).pos.y};
				//DEBUG
				//printf("blit: x %d y %d i %d j %d k %d\n",tmpRect.x,tmpRect.y,i,j,k);
				
				blitCircle(bgSizes[i - 1],screen,tmpRect,(SDL_Color){200,100,0});
				//DEBUG
				//printf("r %d x %d y %d\n",bgSizes[i],tmpRect.x,tmpRect.y);
				//printf("bg-amnt %d\n",i);
			}
		}
	}
}


