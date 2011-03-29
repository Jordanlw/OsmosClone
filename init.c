int initSDL()
{
	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		puts("DEBUG: initSDL() 1");
		return 1;
	}
	SDL_Rect *camera = malloc(sizeof(SDL_Rect));
	camera->x = 0;
	camera->y = 0;
	camera->w = DEFAULT_WIDTH;
	camera->h = DEFAULT_HEIGHT;
	SDL_Surface *screen = SDL_SetVideoMode(camera->w,camera->h,32,SDL_SWSURFACE | SDL_RESIZABLE);
	if(!screen)
	{
		puts("DEBUG: initSDL() 2");
		return 1;
	}
	SDL_Surface *level = SDL_CreateRGBSurface(0,LEVEL_WIDTH,LEVEL_HEIGHT,32,0,0,0,0);
	sdlStore(camera,1);
	sdlStore(screen,2);
	sdlStore(level,16);
	if(initBackground())
	{
		puts("DEBUG: initSDL() 3");
		return 1;
	}
	return 0;
}

static int initBackground()
{
	DIR *directory = opendir(".");
	if(!isFileExist(directory,"resource"))
	{
		puts("DEBUG: initBackground() 1");
		return 1;
	}
	free(directory);
	directory = opendir("resource");
	int amount = 0;
	background *bgs = malloc(sizeof(background) * amount);
	if(!bgs)
	{
		puts("DEBUG: initBackground() 2");
		return 1;
	}
	for(;entry != NULL;)	
	{
		struct dirent entry = readdir(directory);
		if(!strncmp(entry.d_name,"bg",2))
		{
			int len = strlen("resource");
			int lenE = strlen(entry.d_name);
			char *new = malloc(len+lenE+1);
			sprintf(new,"%s%s","resource",entry.d_name);
			bgs[amount].img = SDL_LoadBMP(new);
			free(new);
			bgs[amount].divBy = findNumber(entry.d_name);
			bgs[amount].pos.x = 0;
			bgs[amount].pos.y = 0;
			amount++;			
		}
	}
	sdlStore((void *)&amount,2048);
	return 0;
}

static int findNumber(const char *string)
{
	int i = strlen(string);
	i--;
	char num = 0;
	for(;string[i] != '.' && i >= 0;i--)
	{
	}
	i--;
    char result[BG_INIT_MAX];
	for(;i >= 0;i--)
	{
		num = string[i];
		snprintf(result,BG_INIT_MAX,"%s%s",result,num);
	}
	return atoi(result);
}

int isFileExist(DIR *directory,const char *file)
{
	for(;entry != NULL;)
	{
		struct dirent entry = readdir(directory);
		if(!strcmp(file,entry.d_name))
		{
			return 1;
		}
	}
	return 0;
}
