void velIntoPos(int i)
{
	object *objects = (object *)objectStore(NULL,2);
	objects[i].vel.x += objects[i].force.x / objects[i].radius;
	objects[i].vel.y += objects[i].force.y / objects[i].radius;
	objects[i].pos.x += objects[i].vel.x;
	objects[i].pos.y += objects[i].vel.y;
}
