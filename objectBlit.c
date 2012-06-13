#include <stdlib.h>
#include <math.h>
#include <ppapi/c/pp_size.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/pp_rect.h>

#include "header/objectBlit.h"
#include "header/objectStore.h"
#include "header/store.h"
#include "header/object.h"
#include "header/main.h"
#include "header/blitCircle.h"
#include "header/colorRect.h"

int blitObject()
{
	struct store *stored = GET_STORE();
	object *obj = (object *)objectStore(NULL,GET_OBJECT);
	if(obj == 0)
	{
		puts("DEBUG: blitObject() 2");
		return 1;
	}
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	int i;
	for(i = 0;i < objCount;i++)
	{
		if(obj[i].radius <= 0) continue;
		struct colorRect color = {179,0,21};
		if(i == stored->player)
		{
			color = (struct colorRect){179,95,71};
	 	}
		if(obj[i].radius < obj[stored->player].radius)
		{
			color = (struct colorRect){255,135,102};
		}
		if(blitCircle(obj[i].radius,(struct PP_Point){obj[i].pos.x - stored->camera.point.x,obj[i].pos.y - stored->camera.point.y},color))
		{
			puts("DEBUG: blitObject() 1");
			return 1;
		}
	}
	return 0;
}
