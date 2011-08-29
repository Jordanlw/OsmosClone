#include <sys/time.h>
#include <stdlib.h>

#include "header/random.h"

int randomResult(int high,int low)
{
	struct timeval value;
	gettimeofday(&value,NULL);
	srand(value.tv_usec);
	return (rand() % (high - low + 1) + low);
}
