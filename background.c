#include <SDL/SDL.h>

#include "header/background.h"
#include "header/sdlstore.h"
#include "header/blitCircle.h"

void backgroundBlit(void)
{
	SDL_Rect *camera = sdlStore(NULL,GET_CAMERA);
	SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
	int maxCol = camera->w / BG_WIDTH_SPACING;
	int maxRow = camera->h / BG_HEIGHT_SPACING;
	printf("c: %d, r: %d\n",maxCol,maxRow);
	int col;
	for(col = 0;col < maxCol;col++)
	{
		int row;
		for(row = 0;row < maxRow;row++)
		{
			SDL_Rect pos = {col * BG_WIDTH_SPACING,row * BG_HEIGHT_SPACING,0,0};
			blitCircle(BG_CIRCLE_RADIUS,screen,pos,(SDL_Color){255,255,255});
		}
	}
}


