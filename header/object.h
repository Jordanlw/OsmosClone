typedef struct _doubleRect
{
	double x;
	double y;
	double w;
	double h;
}doubleRect;

typedef struct _object
{
	int type;
	int player;
	unsigned long radius;
	doubleRect vel;
	doubleRect pos;
	doubleRect force;
}object;


