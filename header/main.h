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
#define SPEED 10
#define BG_INIT_MAX 100
#define BG_INIT_SIZE 100

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
#include "levelBlit.h"
#include "pixelMod.h"
#include "debug.h"
#include "varArray.h"

#include "../velIntoPos.c"
#include "../random.c"
#include "../init.c"
#include "../background.c"
#include "../playermovement.c"
#include "../objectStore.c"
#include "../sdlstore.c"
#include "../vectorMath.c"
#include "../movementBoundCheck.c"
#include "../pixelMod.c"
#include "../levelBlit.c"
#include "../debug.c"
#include "../varArray.c"
