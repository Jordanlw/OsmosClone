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
			//blit
			SDL_Rect rect;
			rect.x = (int)pos.x;
			rect.y = (int)pos.y;
			if(isBgVisible(pos))
			{
				SDL_BlitSurface(bgs[i].img,NULL,level,&rect);
			}
			//increment position
			pos.x += bgs[i].img->w;
			if(pos.x > camera->x + camera->w)
			{
				pos.x = camera->x;
				pos.y += bgs[i].img->h;
			}
		}
	}
}

int isBgVisible(vector pos)
{
	SDL_Rect *camera = sdlStore(NULL,4);
	if((int)pos.x > camera->x && (int)pos.x < camera->x + camera->w);
	{
		if((int)pos.y > camera->y && (int)pos.y < camera->y + camera->h)
		{
			return 1;
		}
	}
	return 0;
}

int moreToBlit(vector pos,int current)
{
	SDL_Rect *camera = sdlStore(NULL,4);
	if((int)pos.y > camera->y)
	{
		return 0;
	}
	return 1;
}


