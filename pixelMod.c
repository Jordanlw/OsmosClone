void setPixel32(Uint32 pixel,int x,int y,SDL_Surface *dest)
{
	Uint32 *ptr = (Uint32 *)dest->pixels;
	ptr[(y * dest->w) + x] = pixel;
}
