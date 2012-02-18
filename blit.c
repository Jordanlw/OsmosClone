#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "header/sdlstore.h"

#define LINE_SPACING 5

int blitPause()
{
	static TTF_Font *font = 0;
	if(font == 0)
	{
		font = TTF_OpenFont("resources/fonts/WHITRABT.TTF",15);
	}
	if(font == 0)
	{
		printf("DEBUG: blitPause() 1 - ");
		printf("%s\n",TTF_GetError());
		return 1;
	}
	SDL_Surface *textSur = TTF_RenderText_Solid(font,"Press 'p' to toggle pause state,", \
		(SDL_Color){255,255,255});
	SDL_Surface *screen = sdlStore(NULL,GET_SCREEN);
	if(screen == 0)
	{
		puts("DEBUG: blitPause() 2");
		return 1;
	}
	SDL_BlitSurface(textSur,NULL,screen,&(SDL_Rect){(screen->w / 2) - (textSur->w / 2),(screen->h / 2) - (textSur->h / 2),0,0});
	SDL_Surface *textSur2 = TTF_RenderText_Solid(font,"press it now to play.",(SDL_Color){255,255,255});
	SDL_BlitSurface(textSur2,NULL,screen,&(SDL_Rect){(screen->w / 2) - (textSur2->w / 2),(screen->h / 2) - (textSur2->h / 2) \
		+ (textSur->h + LINE_SPACING)});
	SDL_FreeSurface(textSur);
	SDL_FreeSurface(textSur2);
	return 0;
}
