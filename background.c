#include <stdio.h>
#include <ppapi/c/pp_rect.h>

#include "header/background.h"
#include "header/store.h"
#include "header/blitCircle.h"
#include "header/random.h"
#include "header/object.h"
#include "header/objectStore.h"
#include "header/colorRect.h"

#define COORDS 2
#define BG_MULT 3

int backgroundBlit(void)
{	
	struct store *stored = GET_STORE();
	if(stored->background == 0)
	{
		puts("DEBUG: backgroundBlit() 3");
		return -1;
	}
	if(stored->bgSizes == 0)
	{
		puts("DEBUG: backgroundBlit() 4");
		return -1;
	}
	int bgOffset[BG_AMOUNT][COORDS];
	int i;
	for(i = 0;i < BG_AMOUNT;i++)
	{
		bgOffset[i][0] = ((stored->camera.point.x * BG_MULT) / stored->bgSizes[i]) % stored->camera.size.width;
		bgOffset[i][1] = ((stored->camera.point.y *BG_MULT) / stored->bgSizes[i]) % stored->camera.size.height;
	}
	//Iterate over background layers
	for(i = 0;i < BG_AMOUNT;i++)
	{
		//For tiling
		int mw;
		for(mw = 0;mw < (stored->camera.size.width * 2);mw += BG_INIT_W_SIZE)
		{
			int mh;
			for(mh = 0;mh < (stored->camera.size.height * 2);mh += BG_INIT_H_SIZE)
			{
				int k;
				for(k = 0;k < (MIN_INT(BG_INIT_W_SIZE,stored->camera.size.width) * MIN_INT(BG_INIT_H_SIZE,stored->camera.size.height)) / 
				(BG_INIT_MAX_SPACING * BG_INIT_MAX_SPACING);k++)
				{
					int index = k * (i + 1);
					struct PP_Point tmpRect;
					tmpRect.x = stored->background[index].pos.x + mw - bgOffset[i][0];
					tmpRect.y = stored->background[index].pos.y + mh - bgOffset[i][1];
					blitCircle(stored->bgSizes[i],tmpRect,(struct colorRect){255,255,255});
				}
			}
		}
	}
	return 0;
}


