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
		SDL_Rect sign;
		//Set if positive
		if(relPos.x >= 0) sign.x = 1;
		//Set if negative
		else sign.x = 0;
		if(relPos.y >= 0) sign.y = 1;
		else sign.y = 0;
		//Relpos now equals vector between target and velocity
		relPos.x -= heading.x;
		relPos.y -= heading.y;
		//If relPos is zero & sign is one then enter
		//If relPos is one & sign is zero then enter
		if(!relPos.x == sign.x)
		{
			vector change;
			change.x = (relPos.x - heading.x);
			printf("x: %f\n",change.x);
			relPos.x -= (change.x + 1);
		}
		if(!relPos.y == sign.y)
		{
			vector change;
			change.y = (relPos.y - heading.y);
			printf("y: %f\n",change.y);
			relPos.y -= (change.y + 1);
		}
		/* //DEBUG
		printf("obj: %d sobj: %d\n",i,selectedObj);
		printf("rx: %f ry: %f\n",relPos.x,relPos.y);
		*/
		normalize(&relPos);
		/* //DEBUG
		printf("nrx: %f nry: %f\n",relPos.x,relPos.y);
		printf("vx: %f vy: %f\n",obj[i].vel.x,obj[i].vel.y);
		printf("dist: %f\n",sqrt(relPos.x * relPos.x + relPos.y * relPos.y));
		puts("");
		*/
		obj[i].force.x += SPEED * relPos.x;
		obj[i].force.y += SPEED * relPos.y;
	}
}
