#include <math.h>
#include <stdlib.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/ppb_image_data.h>
#include <ppapi/c/pp_point.h>

#include "header/blitCircle.h"
#include "header/main.h"
#include "header/colorRect.h"
#include "header/store.h"

int blitCircle(unsigned int radius,struct PP_Point offset,struct colorRect color)
{
	struct store *stored = GET_STORE();
	if(stored->pixels == 0)
	{
		puts("DEBUG: blitCircle() 1");
		return 1;
	}
	uint32_t pixelColor = color.r << 24;
	pixelColor += color.g << 16;
	pixelColor += color.b;
	struct PP_ImageDataDesc *desc = malloc(sizeof(struct PP_ImageDataDesc));
	stored->imageInterface->Describe(stored->image,desc);
	//Draw middle line
	int i;
	for(i = 0;i < radius;i++)
	{
		SETPIXEL32(stored->pixels,desc->size,offset.x + i,offset.y,pixelColor);
		SETPIXEL32(stored->pixels,desc->size,offset.x - i,offset.y,pixelColor);
	}
	
	for(i = 0;i < radius;i++)
	{
		unsigned int width = (unsigned int)sqrt((8 * radius * i) - (4 * i * i));
		int j;
		for(j = 0;j < width;j++)
		{
			//Top Right Quarter
			SETPIXEL32(stored->pixels,desc->size,offset.x + (j / 2),offset.y - radius + i,pixelColor);
			//Top Left Quarter
			SETPIXEL32(stored->pixels,desc->size,offset.x - (j / 2),offset.y - radius + i,pixelColor);
			//Bottom Right Quarter
			SETPIXEL32(stored->pixels,desc->size,offset.x + (j / 2),offset.y + radius - i,pixelColor);
			//Bottom Left Quarter
			SETPIXEL32(stored->pixels,desc->size,offset.x - (j / 2),offset.y + radius - i,pixelColor);
		}
	}
	return 0;
}
