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
			int debugSqrt = sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y);
			int overlap =  debugSqrt - (obj[i].radius + obj[j].radius);
			if(overlap > 0) continue;
			overlap = -overlap;
			//DEBUG
			/*
			printf("i %d j %d objCount %d overlap %d relativePos: x %f y %f\n",i,j,objCount,overlap,relativePos.x,relativePos.y);
			printf("combinedRadius: %lu sqrt: %d\n",obj[i].radius + obj[j].radius,debugSqrt);
			*/
			if(obj[j].radius <= obj[i].radius)
			{
				obj[i].radius += overlap ;// MERGE_DIVIDER;
				if(overlap > obj[j].radius)
				{
					obj[j].radius = 0;
				}
				else
				{
					obj[j].radius -= overlap ;// MERGE_DIVIDER;
				}
			}
			else
			{
				obj[j].radius += overlap ;// MERGE_DIVIDER;
				if(overlap > obj[i].radius)
				{
					obj[i].radius = 0;
				}
				else
				{
					obj[i].radius -= overlap ;// MERGE_DIVIDER;
				}
			}
			//DEBUG
			//printf("radius: i %lu j %lu\n\n",obj[i].radius,obj[j].radius);
		}
	}
}
