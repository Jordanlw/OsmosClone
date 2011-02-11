int initObjects()
{
	if(objectStore(NULL,1))
	{
		puts("DEBUG: initOjbects() 1");
		return 1;
	}
	return 0;
}

void *objectStore(void *data,int options)
{
	static object *objects = 0;
	switch(options)
	{
		case 0: break;
	}
	if(options == 1)
	{
		objects = malloc(sizeof(object) * OBJECTS);
		if(!objects)
		{
			puts("DEBUG: objectStore() 1");
			return 1;
		}
		int i;
		for(i = 0;i < OBJECTS;i++)
		{
			objects[i].type = 0;
			objects[i].player = 0;
			objects[i].vel.x = 0;
			objects[i].vel.y = 0;
			objects[i].vel.w = 0;
			objects[i].vel.h = 0;
			objects[i].pos.x = 0;
			objects[i].pos.y = 0;
			objects[i].pos.w = 0;
			objects[i].pos.h = 0;
			objects[i].mass = 0;
			objects[i].force = 0;
		}
		return 0;
	}
	else if(options == 2)
	{
	
	} 
}
