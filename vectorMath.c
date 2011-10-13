#include <math.h>

#include "header/vectorMath.h"

void normalize(vector *A)
{
	double length = sqrt(A->x * A->x + A->y * A->y);
	A->x /= length;
	A->y /= length;
}
