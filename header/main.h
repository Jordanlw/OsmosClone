#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>


#define DEFAULT_WIDTH 500
#define DEFAULT_HEIGHT 500
#define OBJECTS 25
#define LEVEL_WIDTH 3000
#define LEVEL_HEIGHT 3000
#define SPEED 99999
#define BG_INIT_MAX 100
#define BG_INIT_SIZE 100
#define FPS 60

#define SETPIXEL32(surface,x,y,pixel) if(x >= 0 && y >= 0 && x <= ((screen)->w) && y <= ((screen)->h)) \
										 { ((Uint32 *)(surface->pixels))[(y) * ((surface)->w) + (x)] = (pixel); }
#define FIXED_MULT_NORMAL(fixed,normal,ratio) (((fixed) * (normal) * (ratio)) / ((ratio) * (ratio)))

enum
{
	SETCAMERA = 1,
	SETSCREEN = 2,
	GETOBJECT = 2,
	GETCAMERA = 4,
	GETSCREEN = 8,
	SETPLAYER = 64,
	GETPLAYER = 128,
	SETBACKGROUND = 256,
	GETBACKGROUND = 1024,
	SETBACKGROUNDAMOUNT = 2048,
	GETBACKGROUNDAMOUNT = 4096,
	SETFRAMETIME = 3,
	GETFRAMETIME = 5,
};

#include "object.h"
#include "vector.h"
#include "random.h"
#include "init.h"
#include "sdlstore.h"
#include "background.h"
#include "playermovement.h"
#include "objectStore.h"
#include "velIntoPos.h"
#include "vectorMath.h"
#include "movementBoundCheck.h"
#include "debug.h"
#include "varArray.h"
#include "objectBlit.h"

#include "../velIntoPos.c"
#include "../random.c"
#include "../init.c"
#include "../background.c"
#include "../playermovement.c"
#include "../objectStore.c"
#include "../sdlstore.c"
#include "../vectorMath.c"
#include "../movementBoundCheck.c"
#include "../debug.c"
#include "../varArray.c"
#include "../objectBlit.c"
