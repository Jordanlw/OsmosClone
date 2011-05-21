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
	for(i = 0;i < offset->w;i++)
	{
		int j;
		for(j = 0;j < offset->h;j++)
		{
			Uint32 *pixelPtr = (Unint32 *)source->pixels;
			Uint32 pixel = pixelPtr[((j + offset.y) * offset->w) + (i + offset.x)];
			setPixel32(pixel,i,j,target);
		}
	}
}
