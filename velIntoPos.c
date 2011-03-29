void velIntoPos(int i)
{
	object *objects = (object *)objectStore(NULL,2);
	objects[i].vel.x += objects[i].force.x / objects[i].mass;
	objects[i].vel.y += objects[i].force.y / objects[i].mass;
	objects[i].pos.x += objects[i].vel.x;
	objects[i].pos.y += objects[i].vel.y;
}
