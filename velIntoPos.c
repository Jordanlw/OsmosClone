#include <stdlib.h>

#include "header/velIntoPos.h"
#include "header/store.h"
#include "header/objectStore.h"
#include "header/object.h"
#include "header/main.h"

void velIntoPos()
{	
	struct store *stored = GET_STORE();
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	object *objects = (object *)objectStore(NULL,GET_OBJECT);
	int i;
	for(i = 0;i < objCount;i++)
	{
		if(objects[i].radius <= 0) continue;
		objects[i].vel.x += FIXED_MULT_NORMAL(stored->frameTime,objects[i].force.x / objects[i].radius,1000);
		objects[i].vel.y += FIXED_MULT_NORMAL(stored->frameTime,objects[i].force.y / objects[i].radius,1000);
		objects[i].force = (vector){0,0};
		objects[i].pos.x += FIXED_MULT_NORMAL(stored->frameTime,objects[i].vel.x,1000);
		objects[i].pos.y += FIXED_MULT_NORMAL(stored->frameTime,objects[i].vel.y,1000);
	}
}
