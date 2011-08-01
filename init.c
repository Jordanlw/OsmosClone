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
	sdlStore(camera,1);
	sdlStore(screen,2);
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
	for(entry = readdir(directory);entry != NULL;entry = readdir(directory))
	{
		if(!strncmp(entry->d_name,"bg",2))
		{
			int len = strlen("resource");
			int lenE = strlen(entry->d_name);
			char new[len+lenE+1];
			sprintf(new,"%s%s","resource/",entry->d_name);
			bgs[amount].img = SDL_LoadBMP(new);
			if(SDL_SetColorKey(bgs[amount].img,SDL_SRCCOLORKEY,SDL_MapRGB(bgs[amount].img->format,0,255,0)))
			{
				puts("DEBUG: initBackground() 6");
				return 1;
			}
			if(!bgs[amount].img)
			{
				puts("DEBUG: initBackground() 5");
				return 1;
			}
			bgs[amount].divBy = findNumber(entry->d_name) + 1;
			amount++;
			if(amount >= init)
			{
				background *tmp = realloc(bgs,sizeof(background) * init * 2);
				if(!tmp)
				{
					puts("DEBUG: initBackground() 4");
					return 1;
				}
				if(tmp != bgs) free(bgs);
				bgs = tmp;
				init *= 2;
			}
		}
	}
	if(amount < init)
	{
		background *tmp = bgs;
		tmp = realloc(bgs,amount * sizeof(background));
		if(!tmp) 
		{
			puts("DEBUG: initBackground() 3");
		 	return 1;
	 	}
		bgs = tmp;
	}
	sdlStore((void *)bgs,256);
	sdlStore((void *)amount,2048);
	return 0;
}

static int findNumber(const char *string)
{
	char copy[5000];
	strncpy(copy,string,sizeof(copy));
	int i = strlen(copy);
	for(;copy[i] < '0' || copy[i] > '9';i--);
	i++;
	copy[i] = '\0';
	for(i = 0;copy[i] < '0' || copy[i] > '9';i++);
	char tmp[5000];
	strncpy(tmp,copy + i,sizeof(tmp));
	return atoi(tmp);
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
