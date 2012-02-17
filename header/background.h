#ifndef BG_INCLUDE
#define BG_INCLUDE

#include "vector.h"

#define BG_INIT_MAX_SPACING 40
#define BG_INIT_MIN_SPACING 10
#define BG_AMOUNT 3
#define BG_INIT_W_SIZE DEFAULT_WIDTH
#define BG_INIT_H_SIZE DEFAULT_HEIGHT

struct bgData
{
	SDL_Rect pos;
};

void backgroundBlit(void);

#endif
