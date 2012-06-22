#include <math.h>

#include "header/main.h"
#include "header/collisionDetection.h"
#include "header/vectorMath.h"

unsigned int isCollidedObject(object *obj,unsigned int a,unsigned int b)
{
	return isCollidedVectorAndRadius(obj[a].pos,obj[b].pos,obj[a].radius + obj[b].radius);
}

unsigned int isCollidedVectorAndRadius(vector a,vector b,unsigned long radius)
{
	vector relPos;
	FIND_REL_POS(a,b,relPos);
	return radius > sqrt(relPos.x * relPos.x + relPos.y * relPos.y) ? 1 : 0;
}
