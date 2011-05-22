typedef struct _background
{
	SDL_Surface *img;
	vector pos;
	int divBy;
}background;

int isBgVisible(vector );
void backgroundBlit(void);
