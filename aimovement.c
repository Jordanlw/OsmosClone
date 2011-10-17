#include <math.h>
//DEBUG
#include <SDL/SDL.h>

#include "header/object.h"
#include "header/objectStore.h"
#include "header/main.h"
#include "header/sdlstore.h"
#include "header/vectorMath.h"

void moveAiObjects()
{
	//DEBUG
	if(SDL_GetTicks() < 5000) return;

	object *obj = objectStore(NULL,GET_OBJECT);
	int player = *(int *)sdlStore(NULL,GET_PLAYER);
	//Loop through predators objects
	int i;
	for(i = 0;i < OBJECTS;i++)
	{
		if(i == player || obj[i].radius <= 0) continue;
		//Loop for objects to find target
		int selectedObj = -1, imPred = -1;
		double prevDist = -1;
		//Storage for value to determine prefence to targets for predator attacks
		vector relPos;
		int j;
		for(j = 0;j < OBJECTS;j++)
		{
			if(j == i || obj[j].radius <= 0) continue;
			relPos = (vector){obj[j].pos.x - obj[i].pos.x, obj[j].pos.y - obj[i].pos.y};
			double currentDist = sqrt(relPos.x * relPos.x + relPos.y * relPos.y);
			if(prevDist == -1) prevDist = currentDist, selectedObj = j;
			else if(currentDist < prevDist) prevDist = currentDist, selectedObj = j;
			if(obj[selectedObj].radius > obj[i].radius) imPred = 0;
			else imPred = 1;
		}
		//If target hasn't been found, skip the rest (movement to target)
		if(selectedObj == -1) continue;
		relPos = (vector){obj[selectedObj].pos.x - obj[i].pos.x, obj[selectedObj].pos.y - obj[i].pos.y};
		if(imPred == 0) relPos = (vector){-relPos.x, -relPos.y};
		vector heading = obj[i].vel;
		relPos.x -= heading.x;
		relPos.y -= heading.y;
		normalize(&relPos);
		obj[i].force.x += SPEED * relPos.x;
		obj[i].force.y += SPEED * relPos.y;
	}
}
