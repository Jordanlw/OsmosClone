#include <stdlib.h>
#include <SDL/SDL.h>

#include "header/velIntoPos.h"
#include "header/sdlstore.h"
#include "header/objectStore.h"
#include "header/object.h"
#include "header/main.h"

void velIntoPos()
{
	object *objects = (object *)objectStore(NULL,GETOBJECT);
	Uint32 frameTime = *(Uint32 *)sdlStore(NULL,GETFRAMETIME);
	int i;
	for(i = 0;i < OBJECTS;i++)
	{
		if(objects[i].radius <= 0) continue;
		Uint32 frameTime = *(Uint32 *)sdlStore(NULL,GETFRAMETIME);
		objects[i].vel.x += objects[i].force.x / objects[i].radius;
		objects[i].vel.y += objects[i].force.y / objects[i].radius;
		objects[i].force = (vector){0,0};
		objects[i].pos.x += FIXED_MULT_NORMAL((double)frameTime,objects[i].vel.x,1000);
		objects[i].pos.y += FIXED_MULT_NORMAL((double)frameTime,objects[i].vel.y,1000);
	}
}
