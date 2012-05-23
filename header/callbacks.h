#include <semaphore.h>
#include <ppapi/c/pp_instance.h>
#include <ppapi/c/pp_bool.h>

#define NACL_TIME(sem,data,coreInterface) \
	data = malloc(sizeof(struct timeCallbackData)); \
	*data = (struct timeCallbackData){0,sem}; \
	coreInterface->CallOnMainThread(0,PP_MakeCompletionCallback(timeCallback,(void *)data),0); \
	sem_wait(sem);
		
struct inputCallbackData
{
	PP_Instance instance;
	uint32_t flags;
	sem_t *sem;
};

struct g2DCallbackData
{
	PP_Instance instance;
	struct PP_Size *size;
	PP_Bool flag;
	sem_t *sem;
};

struct bindCallbackData
{
	PP_Instance instance;
	PP_Resource screen;
	sem_t *sem;
};

struct timeCallbackData
{
	PP_TimeTicks ticks;
	sem_t *sem;
};

struct mapCallbackData
{
	PP_Resource screen;
	sem_t *sem;
};

struct flushCallbackData
{
	PP_Resource screen;
	sem_t *sem;
};

void inputCallback(void *,int32_t);
void g2DCallback(void *,int32_t);
void bindCallback(void *,int32_t);
void timeCallback(void *,int32_t);
void flushCallback(void *,int32_t);
void mapCallback(void *,int32_t);
