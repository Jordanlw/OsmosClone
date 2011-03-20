void backgroundBlit(void)
{
	int amnt = *sdlStore(NULL,4096);
	for(i = 0;i < amnt;i++)
	{
		updateBackgroundPos(i);
		blitBackground(i);	
	}
}

void updateBackgroundPos(int selected)
{
	background *backgrounds = sdlStore(NULL,1024);
	vector *camera = sdlStore(NULL,4);
	
}

