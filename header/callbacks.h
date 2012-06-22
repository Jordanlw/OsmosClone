#include <semaphore.h>
#include <ppapi/c/pp_instance.h>
#include <ppapi/c/pp_bool.h>
#include <ppapi/c/pp_size.h>

#define CALL_ON_MAIN_THREAD(FUNC,CORE,TYPE,...) (CORE)->CallOnMainThread(0,PP_MakeCompletionCallback((FUNC),(void *)&(TYPE){__VA_ARGS__}),0)

struct inputCallbackData
{
	uint32_t flags;
};

struct g2DCallbackData
{
	int32_t width;
	int32_t height;
	PP_Bool flag;
};

struct bindCallbackData
{
	PP_Resource screen;
};

struct timeCallbackData
{
	PP_TimeTicks *ticks;
	sem_t *sem;
};

struct mapCallbackData
{
	PP_Resource image;
};

struct flushCallbackData
{
	PP_Resource screen;
};

struct imageCallbackData
{
	struct PP_Size size;
	PP_Bool flag;
};

void inputCallback(void *,int32_t);
void g2DCallback(void *,int32_t);
void bindCallback(void *,int32_t);
void timeCallback(void *,int32_t);
void flushCallback(void *,int32_t);
void mapCallback(void *,int32_t);
void imageCallback(void *,int32_t);
