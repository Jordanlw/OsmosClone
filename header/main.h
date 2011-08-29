#define DEFAULT_WIDTH 500
#define DEFAULT_HEIGHT 500
#define OBJECTS 30
#define LEVEL_WIDTH 3000
#define LEVEL_HEIGHT 3000
#define SPEED 1500
#define BG_INIT_MAX 100
#define BG_INIT_SIZE 100
#define FPS 60
#define LEVEL_SIDES 4
#define MERGE_DIVIDER 10
#define MAX_OBJECT_SIZE 100
#define MIN_OBJECT_SIZE 35
#define STARTING_PLAYER_OBJECT_SIZE 130

#define SETPIXEL32(surface,x,y,pixel) if(x >= 0 && y >= 0 && x < ((screen)->w) && y < ((screen)->h)) \
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
