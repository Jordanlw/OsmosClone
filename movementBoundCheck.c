void movementBoundCheck(int i)
{
	object *objects = (object *)objectStore(NULL,2);
	if(objects[i].pos.x - objects[i].radius < 0) objects[i].pos.x = objects[i].radius;
	if(objects[i].pos.x + objects[i].radius > LEVEL_WIDTH) objects[i].pos.x = LEVEL_WIDTH - objects[i].radius;
	if(objects[i].pos.y - objects[i].radius < 0) objects[i].pos.y = objects[i].radius;
	if(objects[i].pos.y + objects[i].radius > LEVEL_HEIGHT) objects[i].pos.y = LEVEL_HEIGHT - objects[i].radius;
}
