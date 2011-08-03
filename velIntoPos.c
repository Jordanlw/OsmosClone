void velIntoPos(int i)
{
	object *objects = (object *)objectStore(NULL,2);
	Uint32 frameTime = *(Uint32 *)sdlStore(NULL,GETFRAMETIME);
	objects[i].vel.x += FIXED_MULT_NORMAL((double)frameTime,(double)objects[i].force.x,1000) / objects[i].radius;
	objects[i].vel.y += FIXED_MULT_NORMAL((double)frameTime,(double)objects[i].force.y,1000) / objects[i].radius;
	objects[i].pos.x += FIXED_MULT_NORMAL((double)frameTime,(double)objects[i].vel.x,1000);
	objects[i].pos.y += FIXED_MULT_NORMAL((double)frameTime,(double)objects[i].vel.y,1000);
}
