#include <stdlib.h>
#include <SDL/SDL.h>

#include "header/velIntoPos.h"
#include "header/sdlstore.h"
#include "header/objectStore.h"
#include "header/object.h"
#include "header/main.h"

void velIntoPos()
{
	object *objects = (object *)objectStore(NULL,GET_OBJECT);
	Uint32 frameTime = *(Uint32 *)sdlStore(NULL,GET_FRAMETIME);
	int i;
	for(i = 0;i < OBJECTS;i++)
	{
		if(objects[i].radius <= 0) continue;
		objects[i].vel.x += FIXED_MULT_NORMAL(frameTime,objects[i].force.x / objects[i].radius,1000);
		objects[i].vel.y += FIXED_MULT_NORMAL(frameTime,objects[i].force.y / objects[i].radius,1000);
		objects[i].force = (vector){0,0};
		objects[i].pos.x += FIXED_MULT_NORMAL((double)frameTime,objects[i].vel.x,1000);
		objects[i].pos.y += FIXED_MULT_NORMAL((double)frameTime,objects[i].vel.y,1000);
	}
}
