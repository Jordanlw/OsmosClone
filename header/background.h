#ifndef BG_INCLUDE
#define BG_INCLUDE

#include "vector.h"

#define BG_INIT_MAX_SPACING 100
#define BG_INIT_MIN_SPACING 100
#define BG_AMOUNT 3
#define BG_SIZE_0 5
#define BG_SIZE_1 10
#define BG_SIZE_2 15

typedef struct _bgData
{
	vector pos;
}bgData;

void backgroundBlit(void);

#endif
