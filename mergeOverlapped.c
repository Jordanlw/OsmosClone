#include <stdio.h>
#include <math.h>

#include "header/mergeOverlapped.h"
#include "header/objectStore.h"
#include "header/object.h"

void mergeOverlapped()
{
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	object *obj = objectStore(NULL,GET_OBJECT);
	int i;
	for(i = 0;i < objCount;i++)
	{
		if(obj[i].radius <= 0) continue;
		int j;
		for(j = 0;j < objCount;j++)
		{
			if(obj[j].radius <= 0 || i == j) continue;
			vector relativePos = {obj[i].pos.x - obj[j].pos.x, obj[i].pos.y - obj[j].pos.y};
			if(obj[i].radius + obj[j].radius <= sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y)) continue;
			if(obj[j].radius <= obj[i].radius) obj[i].radius += (obj[j].radius / MERGE_DIVIDER), obj[j].radius = 0; //printf("%d took %d\n",i,j);
			else obj[j].radius += (obj[i].radius / MERGE_DIVIDER), obj[i].radius = 0; //printf("%d took %d\n",j,i);
		}
	}
}
