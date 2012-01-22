#include <SDL/SDL.h>

#include "header/background.h"
#include "header/sdlstore.h"
#include "header/blitCircle.h"
#include "header/random.h"

#define BG_OFFSET (randomResult(BG_INIT_MAX_SPACING,BG_INIT_MIN_SPACING))

void backgroundBlit(void)
{
	SDL_Rect *camera = sdlStore(NULL,GET_CAMERA);
	SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
	int col;
	for(col = 0;col < camera->w;col += BG_INIT_MAX_SPACING)
	{
		int row;
		for(row = 0;row < camera->h;row += BG_INIT_MAX_SPACING)
		{
			SDL_Rect pos = {col + BG_OFFSET,row + BG_OFFSET,0,0};
			blitCircle(BG_CIRCLE_RADIUS,screen,pos,(SDL_Color){255,255,255});
		}
	}
}


