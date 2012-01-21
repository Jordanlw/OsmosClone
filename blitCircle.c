#include <math.h>

#include "header/blitCircle.h"
#include "header/main.h"

int blitCircle(unsigned int radius,SDL_Surface *surface,SDL_Rect offset,SDL_Color color)
{
	if(surface == 0) 
	{
		puts("DEBUG: blitCircle() 1"); 
		return 1;
	}
	Uint32 pixelColor = SDL_MapRGB(surface->format,color.r,color.g,color.b);
	//Draw middle line
	int i;
	for(i = 0;i < radius;i++)
	{
		SETPIXEL32(surface,offset.x + i,offset.y,pixelColor);
		SETPIXEL32(surface,offset.x - i,offset.y,pixelColor);
	}
	
	for(i = 0;i < radius;i++)
	{
		unsigned int width = (unsigned int)sqrt((8 * radius * i) - (4 * i * i));
		int j;
		for(j = 0;j < width;j++)
		{
			//Top Right Quarter
			SETPIXEL32(surface,offset.x + (j / 2),offset.y - radius + i,pixelColor);
			//Top Left Quarter
			SETPIXEL32(surface,offset.x - (j / 2),offset.y - radius + i,pixelColor);
			//Bottom Right Quarter
			SETPIXEL32(surface,offset.x + (j / 2),offset.y + radius - i,pixelColor);
			//Bottom Left Quarter
			SETPIXEL32(surface,offset.x - (j / 2),offset.y + radius - i,pixelColor);
		}
	}
	return 0;
}
