void backgroundBlit(void)
{
	int *tmp = sdlStore(NULL,4096);
	int amnt = *tmp;
	SDL_Rect *camera = sdlStore(NULL,4);
	background *bgs = sdlStore(NULL,1024);
	SDL_Surface *level = sdlStore(NULL,32);
	int i;
	for(i = 0;i < amnt;i++)
	{
		//update pos
		bgs[i].pos.x = camera->x / bgs[i].divBy;
		bgs[i].pos.y = camera->y / bgs[i].divBy;
		//blit to level
		vector pos;
		pos.x = camera->x;
		pos.y = camera->y;
		while(moreToBlit(pos,i))
		{
			
		}
	}
}

int moreToBlit(vector pos)
{
	SDL_Surface *level = sdlStore(NULL,32);
	if(pos.x > level.w)
	{
		if(pos.y > level.h)
		{
			return 0;
		}
	}
	return 1;
}


