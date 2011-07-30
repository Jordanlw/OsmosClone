void blitObject()
{
	object *obj = objectStore(NULL,GETOBJECT);
	SDL_Rect *camera = sdlStore(NULL,GETCAMERA);
	SDL_Surface *screen = sdlStore(NULL,GETSCREEN);
	int i;
	for(i = 0;i < OBJECTS;i++)
	{
		if(obj[i].radius <= 0) continue;
		int j;
		for(j = 0;j < obj[i].radius;j++)
		{
			unsigned int width = (unsigned int)sqrt(8 * obj[i].radius * j - 4 * j * j);
			int k;
			for(k = 0;k < width;k++)
			{
				SETPIXEL32(screen,(int)(obj[i].pos.x - camera->x - (width / 2) + k),(int)(obj[i].pos.y - camera->y - (obj[i].radius - j) + 1),255);
				SETPIXEL32(screen,(int)(obj[i].pos.x - camera->x - (width / 2) + k),(int)(obj[i].pos.y - camera->y + (obj[i].radius - j) - 1),255);
			}
		}
	}
	SDL_Flip(screen);
	SDL_FillRect(screen,NULL,0);
}
