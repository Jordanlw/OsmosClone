#include <math.h>

#include "header/vectorMath.h"

void normalize(vector *A)
{
	double length = sqrt(A->x * A->x + A->y * A->y);
	if(length)
	{
		A->x /= length;
		A->y /= length;
	}
	else *A = (vector){0,0};
}
