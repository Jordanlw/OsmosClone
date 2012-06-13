#include <math.h>

#include "header/object.h"
#include "header/objectStore.h"
#include "header/main.h"
#include "header/store.h"
#include "header/vectorMath.h"
#include "header/debug.h"

void moveAiObjects()
{
	//DEBUG
	//if(SDL_GetTicks() < 5000) return;
	
	struct store *stored = GET_STORE();
	int objCount = *(int *)objectStore(NULL,GET_OBJ_COUNT);
	object *obj = (object *)objectStore(NULL,GET_OBJECT);
	//Loop through predators objects
	int i;
	for(i = 0;i < objCount;i++)
	{
		if(i == stored->player || obj[i].radius <= 0) continue;
		//Loop for objects to find target
		int selectedObj = -1, imPred = -1;
		double prevDist = -1;
		//Storage for value to determine prefence to targets for predator attacks
		vector relPos;
		int j;
		for(j = 0;j < objCount;j++)
		{
			//Find closest object to "i"
			if(j == i || obj[j].radius <= 0) continue;
			relPos = (vector){obj[j].pos.x - obj[i].pos.x, obj[j].pos.y - obj[i].pos.y};
			double currentDist = sqrt(relPos.x * relPos.x + relPos.y * relPos.y);
			if(prevDist == -1) prevDist = currentDist, selectedObj = j;
			else if(currentDist < prevDist) prevDist = currentDist, selectedObj = j;
			//Determine whether "j" is a predator or prey
			if(obj[selectedObj].radius > obj[i].radius) imPred = 0;
			else imPred = 1;
		}
		//If target hasn't been found, skip the rest (movement to target)
		if(selectedObj == -1) continue;
		//Get vector from predator "i" to selected object
		relPos = (vector){(obj[selectedObj].pos.x + obj[selectedObj].vel.x) - obj[i].pos.x,
		(obj[selectedObj].pos.y + obj[selectedObj].vel.y) - obj[i].pos.y};
		if(imPred == 0) relPos = (vector){-relPos.x, -relPos.y};
		vector heading = obj[i].vel;
		relPos.x -= heading.x;
		relPos.y -= heading.y;
		double velAngle = atan2(heading.y,heading.x);
		double tarAngle = atan2(relPos.y,relPos.x);
		double headAngle = tarAngle;
		if(obj[i].vel.x != 0 && obj[i].vel.y != 0)
		{
 			headAngle = (tarAngle - velAngle) + tarAngle;
		}
		heading = (vector){cos(headAngle),sin(headAngle)};
		if(!headAngle)
		{
			heading = (vector){relPos.x,relPos.y};
			normalize(&heading);
		}
		//DEBUG
		//debugRegister(DEBUG_CALL_BEFORE_BLIT,debugFillRect,(struct debugFillRectData){heading.x * 10,heading.y * 10,10,10,256<<8});
		//printf("i %d, s %d, isPred %d, velAng %.3f, tarAng %.3f, headAng %.3f, headX %.3f, headY %.3f, velX %.1f, velY %.1f\n\n"
		//,i,selectedObj,imPred,velAngle,tarAngle,headAngle,heading.x,heading.y,obj[i].vel.x,obj[i].vel.y);
		/* 
		//DEBUG
		printf("nrx: %f nry: %f\n",relPos.x,relPos.y);
		printf("vx: %f vy: %f\n",obj[i].vel.x,obj[i].vel.y);
		printf("dist: %f\n",sqrt(relPos.x * relPos.x + relPos.y * relPos.y));
		puts("");
		*/
		obj[i].force.x += SPEED * heading.x;
		obj[i].force.y += SPEED * heading.y;
	}
}
