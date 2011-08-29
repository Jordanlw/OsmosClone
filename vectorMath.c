#include <math.h>

#include "header/vectorMath.h"

vector findRelativePos(vector A,vector B)
{
	vector C;
	C.x = A.x - B.x;
	C.y = A.y - B.y;
	return C;
}

void normalize(vector *A)
{
	double length = sqrt(A->x * A->x + A->y * A->y);
	A->x /= length;
	A->y /= length;
}
