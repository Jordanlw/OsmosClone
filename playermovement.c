#include <SDL/SDL.h>

#include "header/playermovement.h"
#include "header/objectStore.h"
#include "header/sdlstore.h"
#include "header/object.h"
#include "header/vectorMath.h"
#include "header/main.h"

void movePlayer(int eventRun,SDL_Event event)
{
	int mouseDown = movePlayerStore(0,2);
	if(event.button.state == SDL_PRESSED && event.button.button == SDL_BUTTON_LEFT) mouseDown = 1;
	if(event.button.state == SDL_RELEASED && event.button.button == SDL_BUTTON_LEFT && eventRun == 0) mouseDown = 0;
	movePlayerStore(mouseDown,1);
}

int movePlayerStore(int data,int option)
{
	static int mouseDown = 0;
	switch(option)
	{
		case 1: mouseDown = data;break;
		case 2: return mouseDown;break;
		default:break;
	}
	return 0;
}

void movePlayerFromData(int player,SDL_Event event)
{
	//only run if the mouse is being pressed down
	int mouseDown = movePlayerStore(0,2);
	if(mouseDown)
	{
		//retrieve data
		object *objects = (object *)objectStore(NULL,2);	
		//retrieve mouse position
		vector mousePos;
		mousePos.x = (double)event.motion.x;
		mousePos.y = (double)event.motion.y;
		//convert mousepos from relative to absolute
		SDL_Rect *camera = (SDL_Rect *)sdlStore(NULL,4);
		mousePos.x += (double)camera->x;
		mousePos.y += (double)camera->y;
		//Convert object data to vector
		vector objectPos;
		objectPos.x = objects[player].pos.x;
		objectPos.y = objects[player].pos.y;
		//subtract coordinates from one another
		vector relative;
		FIND_REL_POS(mousePos,objectPos,relative);
		//find opposing vector from origin of object
		relative.x *= -1;
		relative.y *= -1;
		//divide components by length of vector
		normalize(&relative);
		//determine force, 
		//this should lead to a direction opposite of the mouse position relative the object
		objects[player].force.x = (double)SPEED * relative.x;
		objects[player].force.y = (double)SPEED * relative.y;
	}
}

void moveCamera(int player)
{
	//Get data
	SDL_Rect *camera = sdlStore(NULL,4);
	object *objects = objectStore(NULL,2);
	//Set camera position to center of player object
	camera->x = (int)objects[player].pos.x - (camera->w / 2);
	camera->y = (int)objects[player].pos.y - (camera->h / 2);
	//Adjust camera position so it isn't displaying anything outside of bounds
	if(camera->x < 0) camera->x = 0;
	if(camera->y < 0) camera->y = 0;
	if(camera->x + camera->w > LEVEL_WIDTH) camera->x = LEVEL_WIDTH - camera->w;
	if(camera->y + camera->h > LEVEL_HEIGHT) camera->y = LEVEL_HEIGHT - camera->h;
}
