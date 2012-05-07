#include <ppapi/c/pp_point.h>
#include <ppapi/c/pp_rect.h>

#include "header/playermovement.h"
#include "header/objectStore.h"
#include "header/sdlstore.h"
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
		//retrieve data
		object *obj = (object *)objectStore(NULL,GET_OBJECT);	
		//retrieve mouse position
		struct PP_Point *mousePosInt = (struct PP_Point *)sdlStore(NULL,GET_MOUSE_POS);
		vector mousePos;
		mousePos.x = (double)mousePosInt->x;
		mousePos.y = (double)mousePosInt->y;
		//convert mousepos from relative to absolute
		struct PP_Rect *camera = (struct PP_Rect *)sdlStore(NULL,GET_CAMERA);
		mousePos.x += (double)camera->point.x;
		mousePos.y += (double)camera->point.y;
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
	struct PP_Rect *camera = (struct PP_Rect *)sdlStore(NULL,GET_CAMERA);
	object *objects = (object *)objectStore(NULL,GET_OBJECT);
	int selObj = *(int *)sdlStore(NULL,GET_SELECTED_OBJECT);
	//Set camera position to center of player object
	camera->point.x = (int)objects[selObj].pos.x - (camera->size.width / 2);
	camera->point.y = (int)objects[selObj].pos.y - (camera->size.height / 2);
	//Adjust camera position so it isn't displaying anything outside of bounds
	if(camera->point.x < 0) camera->point.x = 0;
	if(camera->point.y < 0) camera->point.y = 0;
	if(camera->point.x + camera->size.width > LEVEL_WIDTH) camera->point.x = LEVEL_WIDTH - camera->size.width;
	if(camera->point.y + camera->size.height > LEVEL_HEIGHT) camera->point.y = LEVEL_HEIGHT - camera->size.height;
}

void updateSelectedObj(int keyboard)
{
	object *obj = (object *)objectStore(NULL,GET_OBJECT);
	int player = *(int *)sdlStore(NULL,GET_PLAYER);
	if(obj[player].radius != 0)
	{
		return;
	}
	int selObj = *(int *)sdlStore(NULL,GET_SELECTED_OBJECT);
	int down = 0;
	int up = 0;
	switch(keyboard)
	{
		case KEYBOARD_LEFT:
			selObj--;
			down = 1;
			break;
		case KEYBOARD_RIGHT:
			selObj++;
			up = 1;
			break;
	}
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	if(selObj >= objCount)
	{
		selObj = 0;
	}
	if(selObj < 0)
	{
		selObj = objCount - 1;
	}
	if(obj[selObj].radius == 0)
	{
		if(up)
		{
			int i;
			for(i = selObj;;i++)
			{
				if(i >= objCount)
				{
					i = 0;
				}	
				if(obj[i].radius > 0)
				{
					selObj = i;
					break;
				}
			}
		}
		if(down)
		{
			int i;
			for(i = selObj;;i--)
			{
				if(i < 0)
				{
					i = objCount - 1;
				}
				if(obj[i].radius > 0)
				{
					selObj = i;
					break;
				}
			}
		}
	}
	//DEBUG
	//printf("selObj: %d selObj-radius: %lu\n\n",selObj,obj[selObj].radius);
	
	sdlStore((void *)&selObj,SET_SELECTED_OBJECT);
}
