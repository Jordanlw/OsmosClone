void mergeOverlapped()
{
	object *obj = objectStore(NULL,GETOBJECT);
	int i;
	for(i = 0;i < OBJECTS;i++)
	{
		if(obj[i].radius <= 0) continue;
		int j;
		for(j = 0;j < OBJECTS;j++)
		{
			if(obj[j].radius <= 0) continue;
			vector relativePos = {obj[i].pos.x - obj[j].pos.x, obj[i].pos.y - obj[j].pos.y};
			if(obj[i].radius + obj[j].radius >= sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y)) continue;
			if(obj[i].radius <= obj[j].radius) obj[j].radius += (obj[i].radius / MERGE_DIVIDER), obj[i].radius = 0;
			else obj[i].radius += (obj[j].radius / MERGE_DIVIDER), obj[j].radius = 0;
		}
	}
}
