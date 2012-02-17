#include <stdlib.h>

#include "header/movementBoundCheck.h"
#include "header/objectStore.h"
#include "header/main.h"
#include "header/object.h"

void movementBoundCheck()
{
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	int i;
	for(i = 0;i < objCount;i++)
	{
		object *obj = (object *)objectStore(NULL,GET_OBJECT);
		if(obj[i].radius <= 0) continue;
		if(obj[i].pos.x - obj[i].radius < 0) obj[i].pos.x = obj[i].radius, obj[i].vel.x = 0;
		if(obj[i].pos.x + obj[i].radius > LEVEL_WIDTH) obj[i].pos.x = LEVEL_WIDTH - obj[i].radius, obj[i].vel.x = 0;
		if(obj[i].pos.y - obj[i].radius < 0) obj[i].pos.y = obj[i].radius, obj[i].vel.y = 0;
		if(obj[i].pos.y + obj[i].radius > LEVEL_HEIGHT) obj[i].pos.y = LEVEL_HEIGHT - obj[i].radius, obj[i].vel.y = 0;
	}
}
