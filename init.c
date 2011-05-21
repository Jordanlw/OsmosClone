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
	directory = opendir("resource");
	long amount = 0;
	int init = BG_INIT_SIZE;
	background *bgs = malloc(sizeof(background) * init);
	if(!bgs)
	{
		puts("DEBUG: initBackground() 2");
		return 1;
	}
	struct dirent *entry;
	do
	{
		entry = readdir(directory);
		if(!strcmp(entry->d_name,"bg"))
		{
			int len = strlen("resource");
			int lenE = strlen(entry->d_name);
			char new[len+lenE+1];
			sprintf(new,"%s%s","resource",entry->d_name);
			bgs[amount].img = SDL_LoadBMP(new);
			bgs[amount].divBy = findNumber(entry->d_name);
			bgs[amount].pos.x = 0;
			bgs[amount].pos.y = 0;
			amount++;
			if(amount >= init)
			{
				background *tmp = realloc(bgs,sizeof(background) * init * 2);
				if(!tmp)
				{
					puts("DEBUG: initBackground() 4");
					return 1;
				}
				free(bgs);
				bgs = tmp;
				init *= 2;
			}			
		}
	}while(entry != NULL);
	if(amount < init)
	{
		background *tmp = bgs;
		tmp = realloc(bgs,amount);
		if(!tmp) 
		{
			puts("DEBUG: initBackground() 3");
		 	return 1;
	 	}
		free(bgs);
		bgs = tmp;
	}
	sdlStore((void *)bgs,256);
	sdlStore((void *)amount,2048);
	return 0;
}

static int findNumber(const char *string)
{
	int i = strlen(string);
	i--;
	char num = 0;
	for(;string[i] != '.' && i;i--)
	{
	}
	if(i <= 0)
	{
		puts("DEBUG: findNumber() 1");
		return 1;
	}
	i--;
    char result[BG_INIT_MAX];
	for(;i >= 0;i--)
	{
		num = string[i];
		snprintf(result,BG_INIT_MAX,"%s%c",result,num);
	}
	return atoi(result);
}

int isFileExist(DIR *directory,const char *file)
{
	struct dirent *entry;
	do
	{
		entry = readdir(directory);
		if(!strcmp(file,entry->d_name))
		{
			return 1;
		}
	}while(entry != NULL);
	return 0;
}
