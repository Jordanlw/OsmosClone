#include <SDL/SDL.h>

#include "header/debug.h"
#include "header/sdlstore.h"

int debugRegister(int when,int (*func)(void *),void *data)
{
	if(debugStore(&(struct debugMember){func,data,when},SET))
	{
		puts("DEBUG: debugRegister() 1");
		return 1;
	}
	return 0;
}

struct debugMember *debugStore(struct debugMember *data,int options)
{
	static int arraySize = 100;
	static int currentIndex = 0;
	static struct debugMember *array = 0;
	if(currentIndex >= arraySize)
	{
		arraySize *= 2;
		array= realloc(array,arraySize * sizeof(struct debugMember));
		if(!array) 
		{
			puts("DEBUG: debugStore() 1"); 
			return (struct debugMember *)1;
		}
	}
	if(!array)
	{
		array = malloc(arraySize * sizeof(struct debugMember));
		if(!array) 
		{
			puts("DEBUG: debugStore() 2"); 
			return (struct debugMember *)1;
		}
		currentIndex = 1;
	}
	switch(options)
	{
		case GET: return array; break;
		case GET_CURRENT_INDEX: return (struct debugMember *)&currentIndex; break;
		case SET: array[currentIndex] = *array;
	}
	return 0;
}

int debugCall(int when)
{
	struct debugMember *members = debugStore(NULL,GET);
	int currentIndex = *(int *)debugStore(NULL,GET_CURRENT_INDEX);
	int i;
	for(i = 0;i < currentIndex;i++)
	{
		if(members[i].when != when) continue;
		if(members[i].func(members[i].data))
		{
			puts("DEBUG: debugCall() 1"); 
			return 1;
		}
	}
	return 0;
}

int debugFillRect(void *data)
{
	SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
	struct debugFillRectData extractData = *(struct debugFillRectData *)data;
	SDL_FillRect(screen,&(SDL_Rect){extractData.x,extractData.y,extractData.w,extractData.h},extractData.color);
	return 0;
}
