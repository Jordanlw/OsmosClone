#include <math.h>
#include <stdlib.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/ppb_image_data.h>
#include <ppapi/c/pp_point.h>

#include "header/blitCircle.h"
#include "header/main.h"
#include "header/colorRect.h"

int blitCircle(unsigned int radius,struct PP_Point offset,struct colorRect color)
{
	uint32_t *pixels = (uint32_t *)sdlStore(NULL,GET_PIXELS);
	if(pixels == 0)
	{
		puts("DEBUG: blitCircle() 1");
		return 1;
	}
	uint32_t pixelColor = color.r << 24;
	pixelColor += color.g << 16;
	pixelColor += color.b;
	PPB_ImageData *imageInterface = (PPB_ImageData *)sdlStore(NULL,GET_IMAGE_INTERFACE);
	PP_Resource screen = sdlStore(NULL,GET_SCREEN);
	struct PP_ImageDataDesc *desc = (struct PP_ImageDataDesc *)malloc(sizeof(struct PP_ImageDataDesc));
	imageInterface->Describe(screen,desc);
	//Uint32 pixelColor = SDL_MapRGB(surface->format,color.r,color.g,color.b);
	//Draw middle line
	int i;
	for(i = 0;i < radius;i++)
	{
		SETPIXEL32(pixels,desc->size,offset.x + i,offset.y,pixelColor);
		SETPIXEL32(pixels,desc->size,offset.x - i,offset.y,pixelColor);
	}
	
	for(i = 0;i < radius;i++)
	{
		unsigned int width = (unsigned int)sqrt((8 * radius * i) - (4 * i * i));
		int j;
		for(j = 0;j < width;j++)
		{
			//Top Right Quarter
			SETPIXEL32(pixels,desc->size,offset.x + (j / 2),offset.y - radius + i,pixelColor);
			//Top Left Quarter
			SETPIXEL32(pixels,desc->size,offset.x - (j / 2),offset.y - radius + i,pixelColor);
			//Bottom Right Quarter
			SETPIXEL32(pixels,desc->size,offset.x + (j / 2),offset.y + radius - i,pixelColor);
			//Bottom Left Quarter
			SETPIXEL32(pixels,desc->size,offset.x - (j / 2),offset.y + radius - i,pixelColor);
		}
	}
	return 0;
}
