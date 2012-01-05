#include "header/blitCircle.h"
#include <SDL/SDL.h>

int blitCircle(unsigned int radius,SDL_Surface *surface,SDL_Rect offset,SDL_Color color)
{
	if(surface == 0) puts("DEBUG: blitCircle() 1"), return -1;
	pixelColor = SDL_MapRGB(surface->format,color.r,color.g,color.b);
	int i;
	for(i = 0;i < radius;i++)
	{
		unsigned int width = (unsigned int)sqrt(8 * radius * j - 4 * j * j);
		int j;
		for(j = 0;j < width;j++)
		{
			SETPIXEL32(screen,offset.x - (width / 2) + j,offset.y - (radius - i) + 1,pixelColor);
			SETPIXEL32(screen,offset.x - (width / 2) + j,offset.y + (radius - i) - 1,pixelColor);
		}
	}
}
