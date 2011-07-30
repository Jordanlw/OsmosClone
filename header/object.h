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
	int radius;
	doubleRect vel;
	doubleRect pos;
	double mass;
	doubleRect force;
}object;


