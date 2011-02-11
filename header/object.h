typedef struct _object
{
	int type;
	int player;
	SDL_Rect vel;
	SDL_Rect pos;
	double mass;
	double force;
}object;
