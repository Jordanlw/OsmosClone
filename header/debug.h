#include <stdio.h>
#include <stdlib.h>

struct debugMember
{
	int (*func)(void *);
	void *data;
	int when;
};

struct debugFillRectData
{
	unsigned int x,y,w,h,color;
};

enum
{
	SET,
	GET,
	GET_CURRENT_INDEX,
	
	DEBUG_CALL_BEFORE_BLIT
};

int debugRegister(int ,int (*)(void *),void *);
struct debugMember *debugStore(struct debugMember *,int );
int debugCall(int);
int debugFillRect(void *);
