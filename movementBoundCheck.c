void movementBoundCheck(int i)
{
	object *objects = (object *)objectStore(NULL,2);
	if(objects[i].pos.x > LEVEL_WIDTH)
	{
		objects[i].pos.x = LEVEL_WIDTH;
	}
	else if(objects[i].pos.x < 0)
	{
		objects[i].pos.x = 0;
	}
	if(objects[i].pos.y > LEVEL_HEIGHT)
	{
		objects[i].pos.y = LEVEL_HEIGHT;
	}
	else if(objects[i].pos.y < 0)
	{
		objects[i].pos.y = 0;
	}
}
