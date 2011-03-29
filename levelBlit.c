void blitLevel()
{
	SDL_Surface *level = sdlStore(NULL,32);
	SDL_Surface *screen = sdlStore(NULL,8);
	SDL_Rect *camera = sdlStore(NULL,4);
	blitAtOffset(screen,level,camera);	
}

void blitAtOffset(SDL_Surface *target,SDL_Surface *source,SDL_Rect *offset)
{
	int i;
	for(i = offset->x;i < offset->w + offset->x;i++)
	{
		int j;
		for(j = offset->y;j < offset->h + offset->y;j++)
		{
			Uint32 *ptr = (Uint32 *)source->pixels;
			Uint32 pixel = ptr[(i * offset->h) + j];
			setPixel32(pixel,i - offset->x,j - offset->y,target);
		}
	}
}
