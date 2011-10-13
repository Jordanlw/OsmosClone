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
		int target = -1, biggestPredator = -1;
		//Storage for value to determine prefence to targets for predator attacks
		int targetPrefValue = 0;
		int relX, relY;
		int j;
		for(j = 0;j < OBJECTS;j++)
		{
			if(j == i || obj[j].radius <= 0 || obj[i].radius < obj[j].radius) continue;
			relX = obj[j].pos.x - obj[i].pos.x;
			relY = obj[j].pos.y - obj[i].pos.y;
			int prefValue = obj[j].radius * sqrt(relX * relX + relY * relY);
			if(prefValue < targetPrefValue || targetPrefValue == 0)
			{
				targetPrefValue = prefValue;
				target = j;
			}
			if(prefValue > targetPrefValue) biggestPredator = j;
		}
		//If target hasn't been found, skip the rest (movement to target)
		if(target == -1 && biggestPredator == -1) continue;
		if(biggestPredator != -1 && target == -1)
		{
			relX = obj[i].pos.x - obj[biggestPredator].pos.x;
			relY = obj[i].pos.y - obj[biggestPredator].pos.y;
		}
		vector normedRel = (vector){relX,relY};
		normalize(&normedRel);
		obj[i].force.x += normedRel.x * SPEED;
		obj[i].force.y += normedRel.y * SPEED;
		//DEBUG
		//printf("p: %d t: %d\n",i,target);
		//printf("x: %f y: %f d: %f\n",normedRel.x,normedRel.y,sqrt(normedRel.x * normedRel.x + normedRel.y * normedRel.y));
	}
}
