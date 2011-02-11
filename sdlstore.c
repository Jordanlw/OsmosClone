void *sdlStore(void *data,int option)
{
	static SDL_Surface *screen = 0;
	static SDL_Rect *camera = 0;
	if(option)
	{
		switch(option)
		{
			case 1:camera = (SDL_Rect *)data;break;
			case 2:screen = (SDL_Screen *)data;break;
			case 4:return (void *)camera;break;
			case 8:return (void *)screen;break;
			default:break;
		}
	}
	return 0;
}
