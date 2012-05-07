#include <stdlib.h>
#include <math.h>
#include <ppapi/c/pp_size.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/pp_rect.h>

#include "header/objectBlit.h"
#include "header/objectStore.h"
#include "header/sdlstore.h"
#include "header/object.h"
#include "header/main.h"
#include "header/blitCircle.h"
#include "header/colorRect.h"

int blitObject()
{
	object *obj = (object *)objectStore(NULL,GET_OBJECT);
	if(obj == 0)
	{
		puts("DEBUG: blitObject() 2");
		return 1;
	}
	struct PP_Rect *camera = (struct PP_Rect *)sdlStore(NULL,GET_CAMERA);
	if(camera == 0)
	{
		puts("DEBUG: blitObject() 3");
		return 1;
	}
	PP_Resource screen = *(PP_Resource *)sdlStore(NULL,GET_SCREEN);
	if(screen == 0)
	{
		puts("DEBUG: blitObject() 4");
		return 1;
	}
	int player = *(int *)sdlStore(NULL,GET_PLAYER);
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	int i;
	for(i = 0;i < objCount;i++)
	{
		if(obj[i].radius <= 0) continue;
		struct colorRect color = {179,0,21};
		if(i == player)
		{
			color = (struct colorRect){179,95,71};
	 	}
		if(obj[i].radius < obj[player].radius)
		{
			color = (struct colorRect){255,135,102};
		}
		if(blitCircle(obj[i].radius,(struct PP_Point){obj[i].pos.x - camera->point.x,obj[i].pos.y - camera->point.y},color))
		{
			puts("DEBUG: blitObject() 1");
			return 1;
		}
	}
	return 0;
}
