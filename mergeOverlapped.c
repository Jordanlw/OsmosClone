#include <stdio.h>
#include <math.h>

#include "header/mergeOverlapped.h"
#include "header/objectStore.h"
#include "header/object.h"

static void internalMacro(int,int,object *,int);

void mergeOverlapped()
{
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	object *obj = (object *)objectStore(NULL,GET_OBJECT);
	int i;
	for(i = 0;i < objCount;i++)
	{
		if(obj[i].radius <= 0) continue;
		int j;
		for(j = 0;j < objCount;j++)
		{
			if(obj[j].radius <= 0 || i == j) continue;
			vector relativePos = {obj[i].pos.x - obj[j].pos.x, obj[i].pos.y - obj[j].pos.y};
			int overlap =  sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y) - (obj[i].radius + obj[j].radius);
			if(overlap >= 0) continue;
			overlap = -overlap;
			//DEBUG
			/*
			printf("i %d j %d objCount %d overlap %d relativePos: x %f y %f\n",i,j,objCount,overlap,relativePos.x,relativePos.y);
			printf("combinedRadius: %lu sqrt: %d\n",obj[i].radius + obj[j].radius,debugSqrt);
			*/
			/*
			printf("i: %d j: %d\n",i,j);
			printf("overlap: %d\n",overlap);
			printf("radius: i %lu j %lu\n",obj[i].radius,obj[j].radius);
			*/
			if(obj[j].radius <= obj[i].radius)
			{
				//puts("J smaller");
				internalMacro(i,j,obj,overlap);
			}
			else
			{
				//puts("I smaller");
				internalMacro(j,i,obj,overlap);
			}
			//DEBUG
			//puts("");
		}
	}
}
static void internalMacro(int objA,int objB,object * obj,int overlap)
{
	if(overlap > obj[objB].radius)
	{
		overlap = obj[objB].radius;
	}
	int surfaceArea = (pow(obj[objB].radius,2) * M_PI) - (pow(obj[objB].radius - overlap,2) * M_PI);
	surfaceArea += pow(obj[objA].radius,2) * M_PI;
	//DEBUG
	//printf("surfaceArea-Before: %d\n",surfaceArea);
	
	surfaceArea = sqrt(surfaceArea / M_PI);
	//DEBUG
	/*
	printf("surfaceArea: %d\n",surfaceArea);
	printf("arg1: %f arg2: %f\n",pow(obj[objB].radius,2) * M_PI,pow(obj[objB].radius - overlap,2) * M_PI);
	*/
	obj[objA].radius = surfaceArea;
	if(overlap > obj[objB].radius)
	{
		obj[objB].radius = 0;
	}
	else
	{
		obj[objB].radius -= overlap;
	}
	//puts("");
}
