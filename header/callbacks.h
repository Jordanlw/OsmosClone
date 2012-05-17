#include <ppapi/c/pp_instance.h>
#include <ppapi/c/pp_bool.h>

struct inputCallbackData
{
	PP_Instance instance;
	uint32_t flags;
};

struct g2DCallbackData
{
	PP_Instance instance;
	struct PP_Size *size;
	PP_Bool flag;
	
};

void inputCallback(void *,int32_t);
void g2DCallback(void *,int32_t);
