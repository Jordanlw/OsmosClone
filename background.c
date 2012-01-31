#include <SDL/SDL.h>

#include "header/background.h"
#include "header/sdlstore.h"
#include "header/blitCircle.h"
#include "header/random.h"
#include "header/object.h"
#include "header/objectStore.h"

#define COORDS 2

#define GET_INIT_DATA(x,y,layer,initSize,array) (array[(((y) * ((initSize) / (BG_INIT_MAX_SPACING)) + (x)) * ((layer) + 1))])

#define INIT_PLACEHOLDER(initSize) (GET_INIT_DATA(k,j,i,initSize,initData).pos)

void backgroundBlit(void)
{
	SDL_Rect *camera = sdlStore(NULL,GET_CAMERA);
	SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
	bgData *initData = sdlStore(NULL,GET_BACKGROUND);
	int *bgSizes = (int *)sdlStore(NULL,GET_BG_SIZE);
	//DEBUG
	//printf("cw / initw %d\n",camera->w / BG_INIT_W_SIZE);
	//printf("bg: %p\n",bgSizes);
	
	int bgOffset[BG_AMOUNT][COORDS];
	int i;
	for(i = 0;i < BG_AMOUNT;i++)
	{
		bgOffset[i][0] = mult % camera->w;
		bgOffset[i][1] = mult % camera->h;
		//DEBUG
		//printf("cx %d s %d o-b %d m %d\n",camera->x,bgSizes[i],bgOffset[i],mult);
		printf("bg %d\n",bgOffset[i]);
	}
	
	//Iterate over background layers
	for(i = 1;i <= BG_AMOUNT;i++)
	{
		//For tiling
		int mw;
		for(mw = 0;mw < camera->w + bgOffset[i][0];mw += BG_INIT_W_SIZE)
		{
			int mh;
			for(mh = 0;mh < camera->h + bgOffset[i][1];mh += BG_INIT_H_SIZE)
			{
				int j;
				for(j = 0;j < MIN_INT(BG_INIT_H_SIZE,camera->h) / BG_INIT_MAX_SPACING;j++)
				{
					int k;
					for(k = 0;k < MIN_INT(BG_INIT_W_SIZE,camera->w) / BG_INIT_MAX_SPACING;k++)
					{
						int ix = INIT_PLACEHOLDER(BG_INIT_W_SIZE).x + mw - bgOffset[i][0];
						int iy = INIT_PLACEHOLDER(BG_INIT_H_SIZE).y + mh - bgOffset[i][1];
						SDL_Rect tmpRect = (SDL_Rect){ix,iy};
						//DEBUG
						//printf("blit: x %d y %d i %d j %d k %d mw %d\n",tmpRect.x,tmpRect.y,i,j,k,mw);
				
						blitCircle(bgSizes[i],screen,tmpRect,(SDL_Color){200,100,0});
						//DEBUG
						//printf("r %d x %d y %d\n",bgSizes[i],tmpRect.x,tmpRect.y);
						//printf("bg-amnt %d\n",i);
					}
				}
			}
		}
	}
	//DEBUG
	//puts("");
	//puts("DEBUG: calling exit() in background.c");
	//exit(0);
}


