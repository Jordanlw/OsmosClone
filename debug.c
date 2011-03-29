void debug(SDL_Event event,int pl)
{
	object *obs = objectStore(NULL,2);
	int mx = event.motion.x;
	int my = event.motion.y;
	printf("MX %d MY %d\n",mx,my);
	printf("OX %f OY %f\n",obs[pl].pos.x,obs[pl].pos.y);
	printf("FX %f FY %f\n",obs[pl].force.x,obs[pl].force.y);
	puts("");
	SDL_Delay(500);
}
