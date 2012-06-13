#include <ppapi/c/pp_point.h>
#include <ppapi/c/pp_rect.h>

#include "header/playermovement.h"
#include "header/objectStore.h"
#include "header/store.h"
#include "header/object.h"
#include "header/vectorMath.h"
#include "header/main.h"

/*
void movePlayer(SDL_Event event)
{
	int mouseDown = movePlayerStore(0,GET_PLAYER_STORE_MOUSE_DOWN);
	if(event.button.state == SDL_PRESSED && event.button.button == SDL_BUTTON_LEFT) mouseDown = 1;
	else if(event.button.state == SDL_RELEASED && event.button.button == SDL_BUTTON_LEFT) mouseDown = 0;
	movePlayerStore(mouseDown,SET_PLAYER_STORE_MOUSE_DOWN);
}
*/
int movePlayerStore(int data,int option)
{
	static int mouseDown = 0;
	switch(option)
	{
		case SET_PLAYER_STORE_MOUSE_DOWN: mouseDown = data;break;
		case GET_PLAYER_STORE_MOUSE_DOWN: return mouseDown;break;
		default:break;
	}
	return 0;
}

void movePlayerFromData(int player)
{
	//only run if the mouse is being pressed down
	int mouseDown = movePlayerStore(0,GET_PLAYER_STORE_MOUSE_DOWN);
	if(mouseDown)
	{
		struct store *stored = GET_STORE();
		//retrieve data
		object *obj = (object *)objectStore(NULL,GET_OBJECT);	
		//retrieve mouse position
		vector mousePos;
		mousePos.x = stored->mousePos.x;
		mousePos.y = stored->mousePos.y;
		//convert mousepos from relative to absolute
		mousePos.x += stored->camera.point.x;
		mousePos.y += stored->camera.point.y;
		//Convert object data to vector
		vector objPos;
		objPos.x = obj[player].pos.x;
		objPos.y = obj[player].pos.y;
		//subtract coordinates from one another
		vector relative;
		FIND_REL_POS(mousePos,objPos,relative);
		//find opposing vector from origin of object
		relative.x = -relative.x;
		relative.y = -relative.y;
		//divide components by length of vector
		normalize(&relative);
		//determine force, 
		//this should lead to a direction opposite of the mouse position relative the object
		obj[player].force.x = (double)SPEED * relative.x;
		obj[player].force.y = (double)SPEED * relative.y;
	}
}

void moveCamera()
{
	//Get data
	struct store *stored = GET_STORE();
	object *objects = (object *)objectStore(NULL,GET_OBJECT);
	//Set camera position to center of player object
	stored->camera.point.x = (int)objects[stored->selObj].pos.x - (stored->camera.size.width / 2);
	stored->camera.point.y = (int)objects[stored->selObj].pos.y - (stored->camera.size.height / 2);
	//Adjust camera position so it isn't displaying anything outside of bounds
	if(stored->camera.point.x < 0) stored->camera.point.x = 0;
	if(stored->camera.point.y < 0) stored->camera.point.y = 0;
	if(stored->camera.point.x + stored->camera.size.width > LEVEL_WIDTH) stored->camera.point.x = LEVEL_WIDTH - stored->camera.size.width;
	if(stored->camera.point.y + stored->camera.size.height > LEVEL_HEIGHT) stored->camera.point.y = LEVEL_HEIGHT - stored->camera.size.height;
}

void updateSelectedObj(int keyboard)
{
	struct store *stored = GET_STORE();
	object *obj = (object *)objectStore(NULL,GET_OBJECT);
	if(obj[stored->player].radius != 0)
	{
		return;
	}
	int down = 0;
	int up = 0;
	switch(keyboard)
	{
		case KEYBOARD_LEFT:
			stored->selObj--;
			down = 1;
			break;
		case KEYBOARD_RIGHT:
			stored->selObj++;
			up = 1;
			break;
	}
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	if(stored->selObj >= objCount)
	{
		stored->selObj = 0;
	}
	if(stored->selObj < 0)
	{
		stored->selObj = objCount - 1;
	}
	if(obj[stored->selObj].radius == 0)
	{
		if(up)
		{
			int i;
			for(i = stored->selObj;;i++)
			{
				if(i >= objCount)
				{
					i = 0;
				}	
				if(obj[i].radius > 0)
				{
					stored->selObj = i;
					break;
				}
			}
		}
		if(down)
		{
			int i;
			for(i = stored->selObj;;i--)
			{
				if(i < 0)
				{
					i = objCount - 1;
				}
				if(obj[i].radius > 0)
				{
					stored->selObj = i;
					break;
				}
			}
		}
	}
}
