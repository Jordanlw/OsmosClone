#ifndef INCLUDE_MAIN
#define INCLUDE_MAIN

#define DEFAULT_WIDTH 500
#define DEFAULT_HEIGHT 500
#define OBJECTS 10
#define LEVEL_WIDTH 3000
#define LEVEL_HEIGHT 3000
#define SPEED 25000
#define BG_INIT_MAX 100
#define BG_INIT_SIZE 100
#define FPS 60
#define LEVEL_SIDES 4
#define MERGE_DIVIDER 10
#define MAX_OBJECT_SIZE 150
#define MIN_OBJECT_SIZE 50
#define STARTING_PLAYER_OBJECT_SIZE 100

#define SETPIXEL32(surface,x,y,pixel) if(x >= 0 && y >= 0 && x < ((surface)->w) && y < ((surface)->h)) \
										 { ((Uint32 *)(surface->pixels))[((y) * ((surface)->w)) + (x)] = (pixel); }
										 
#define FIXED_MULT_NORMAL(fixed,normal,ratio) (((fixed) * (normal) * (ratio)) / ((ratio) * (ratio)))

#define FIND_REL_POS(inputA,inputB,output) (((output).x) = ((inputA).x) - ((inputB).x)); (((output).y) = ((inputA).y) - ((inputB).y))

#define MIN_INT(a,b) ((a) < (b) ? (a) : (b))

enum
{
	
	GET_OBJECT, 
	GET_CAMERA,
	GET_SCREEN, 
	GET_FRAMETIME,
	GET_PLAYER_STORE_MOUSE_DOWN,
	GET_PLAYER, 
	GET_BACKGROUND,
	GET_BG_SIZE,
	 
	SET_BACKGROUND,
	SET_BG_SIZE,
	SET_FRAMETIME,
	SET_PLAYER,	
	SET_PLAYER_STORE_MOUSE_DOWN,
	SET_CAMERA,
	SET_SCREEN,
	
	CREATE_OBJECTS,
	INIT_PAUSE
};

#endif //ifndef INCLUDE_MAIN 
