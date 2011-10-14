#include <math.h>
//DEBUG
#include <SDL/SDL.h>
//#include <stdio.h>

#include "header/object.h"
#include "header/objectStore.h"
#include "header/main.h"
#include "header/sdlstore.h"
#include "header/vectorMath.h"

void moveAiObjects()
{
	//DEBUG
	if(SDL_GetTicks() < 5000) return;

	object *obj = objectStore(NULL,GETOBJECT);
	int player = *(int *)sdlStore(NULL,GETPLAYER);
	//Loop through predators objects
	int i;
	for(i = 0;i < OBJECTS;i++)
	{
		if(i == player || obj[i].radius <= 0) continue;
		//Loop for objects to find target
		int target = -1, bigPred = 0, bigPredSet = 0;
		//Storage for value to determine prefence to targets for predator attacks
		int targetPrefValue = -1;
		vector relPos;
		int j;
		for(j = 0;j < OBJECTS;j++)
		{
			if(j == i || obj[j].radius <= 0) continue;
			relPos.x = obj[j].pos.x - obj[i].pos.x;
			relPos.y = obj[j].pos.y - obj[i].pos.y;
			int prefValue = obj[j].radius * sqrt(relPos.x * relPos.x + relPos.y * relPos.y);
			if((prefValue < targetPrefValue || targetPrefValue == -1) && obj[j].radius <= obj[i].radius)
			{
				targetPrefValue = prefValue;
				target = j;
			}
			if(obj[j].radius >= obj[bigPred].radius) bigPred = j, bigPredSet = 1;
		}
		//If target hasn't been found, skip the rest (movement to target)
		if(target == -1 && bigPredSet == 0) continue;
		if(bigPredSet == 1 && targetPrefValue == -1)
		{
			relPos = (vector){obj[i].pos.x - obj[bigPred].pos.x,obj[i].pos.y - obj[bigPred].pos.y};
		}
		vector heading = obj[i].vel;
		relPos.x -= heading.x;
		relPos.y -= heading.y;
		normalize(&relPos);
		obj[i].force.x += SPEED * relPos.x;
		obj[i].force.y += SPEED * relPos.y;
	}
}
