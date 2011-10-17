#include <stdio.h>
#include <stdlib.h>

#include "header/objectStore.h"
#include "header/object.h"

int initObjects()
{
	if(objectStore(NULL,CREATE_OBJECTS))
	{
		puts("DEBUG: initOjbects() 1");
		return 1;
	}
	return 0;
}

void *objectStore(void *data,int options)
{
	static object *objects = 0;
	switch(options)
	{
		case GET_OBJECT: return (void *)objects;break;
		default: break;
	}
	//create objects
	if(options == CREATE_OBJECTS)
	{
		objects = malloc(sizeof(object) * OBJECTS);
		if(!objects)
		{
			puts("DEBUG: objectStore() 1");
			return (void *)1;
		}
		int i;
		for(i = 0;i < OBJECTS;i++)
		{
			objects[i].type = 0;
			objects[i].player = 0;
			objects[i].radius = 0;
			objects[i].vel.x = 0;
			objects[i].vel.y = 0;
			objects[i].pos.x = 0;
			objects[i].pos.y = 0;
			objects[i].force.x = 0;
			objects[i].force.y = 0;
		}
	}
	return (void *)0;
}
