#include <math.h>

#include "header/collisionDetection.h"
#include "header/vectorMath.h"

inline unsigned int isCollidedObject(object *obj,unsigned int a,unsigned int b)
{
	return isCollidedVectorAndRadius(obj[a].pos,obj[b].pos,obj[a].radius + obj[b].radius);
}

inline unsigned int isCollidedVectorAndRadius(vector a,vector b,unsigned long radius)
{
	vector relPos = findRelativePos(a,b);
	return radius > sqrt(relPos.x * relPos.x + relPos.y * relPos.y) ? 1 : 0;
}
