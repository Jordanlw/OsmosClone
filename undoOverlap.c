void underOverlap()
{
	object *obj = objectStore(NULL,GETOBJECT);
	int j;
	for(j = 0;j < OBJECTS;j++)
	{
		if(obj[j].radius <= 0) continue;
		int i;
		for(i = 0;i < OBJECTS;i++)
		{
			if(j == i || obj[i].radius <= 0) continue;
			int combinedRadius = obj[j].radius + obj[i].radius;
			vector relativePos = findRelativePos(obj[j].pos,obj[i].pos);
			double distance = sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y);
			if(distance >= combinedRadius) continue;
			double angle = atan2(obj[i].pos.y - obj[j].pos.y,obj[i].pos.x - obj[j].pos.x);
			double radius = obj[j].radius + obj[i].radius;
			obj[i].pos.x = (cos(angle) * radius) + obj[j].pos.x;
			obj[i].pos.y = (sin(angle) * radius) + obj[j].pos.y;
		}
	}
}
