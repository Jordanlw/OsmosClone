typedef struct _background
{
	SDL_Surface *img;
	vector pos;
	int divBy;
}background;

int moreToBlit(vector ,int );
int isBgVisible(vector );
void backgroundBlit(void);
