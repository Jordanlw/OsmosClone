void blitLevel()
{
	SDL_Surface *level = sdlStore(NULL,32);
	SDL_Surface *screen = sdlStore(NULL,8);
	SDL_Rect *camera = sdlStore(NULL,4);
	SDL_Rect offset;
	offset.x = camera->x;
	offset.y = camera->y;
	SDL_BlitSurface(screen,NULL,level,&offset);
}

