#include <unistd.h>
#include <stdio.h>
#include <ppapi/c/ppb_input_event.h>
#include <ppapi/c/pp_errors.h>
#include <ppapi/c/ppb_graphics_2d.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppb_core.h>

#include "header/sdlstore.h"
#include "header/main.h"
#include "header/callbacks.h"

void inputCallback(void *data,int32_t result)
{
	PPB_InputEvent *inputInterface = (PPB_InputEvent *)sdlStore(NULL,GET_INPUT_INTERFACE);
	struct inputCallbackData *readyData = (struct inputCallbackData *)data;
	int32_t returnValue = inputInterface->RequestInputEvents(readyData->instance,readyData->flags);
	if(returnValue == PP_ERROR_BADARGUMENT)
	{
		puts("DEBUG: inputCallback() 1");
		exit(1);
	}
	else if(returnValue == PP_ERROR_NOTSUPPORTED)
	{
		puts("DEBUG: inputCallback() 2");
		exit(1);
	}
	sem_post(readyData->sem);
	return;
}

void g2DCallback(void *data,int32_t result)
{
	PPB_Graphics2D *g2DInterface = (PPB_Graphics2D *)sdlStore(NULL,GET_2D_INTERFACE);
	struct g2DCallbackData *readyData = (struct g2DCallbackData *)data;
	PP_Resource screen = g2DInterface->Create(readyData->instance,readyData->size,readyData->flag);
	sdlStore((void *)&screen,SET_SCREEN);
	sem_post(readyData->sem);
	return;
}

void bindCallback(void *data,int32_t result)
{
	PPB_Instance *instanceInterface = (PPB_Instance *)sdlStore(NULL,GET_INSTANCE_INTERFACE);
	struct bindCallbackData *readyData = (struct bindCallbackData *)data;
	if(instanceInterface->BindGraphics(readyData->instance,readyData->screen) == PP_FALSE)
	{
		puts("DEBUG: bindCallback() 1");
		exit(1);
	}
	sem_post(readyData->sem);
	return;
}

void timeCallback(void *data,int32_t result)
{
	PPB_Core *coreInterface = sdlStore(NULL,GET_CORE_INTERFACE);
	struct timeCallbackData *readyData = (struct timeCallbackData *)data;
	readyData->ticks = coreInterface->GetTimeTicks() * 1000;
	sem_post(readyData->sem);
	return;
}
