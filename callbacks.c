#include <unistd.h>
#include <stdio.h>
#include <ppapi/c/ppb_input_event.h>
#include <ppapi/c/pp_errors.h>
#include <ppapi/c/ppb_graphics_2d.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppb_core.h>
#include <ppapi/c/ppb_image_data.h>

#include "header/store.h"
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
	//DEBUG
	printf("DEBUG: g2DCallback() - instance = %d, size[w = %d, h = %d], flag = %d\n", \
		readyData->instance,readyData->size->width,readyData->size->height,readyData->flag);
	printf("DEBUG: g2DCallback() - screen = %d\n",screen);
	
	if(screen == 0)
	{
		puts("DEBUG: g2DCallback() 1");
		exit(1);
	}
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
	readyData->ticks = coreInterface->GetTimeTicks();
	sem_post(readyData->sem);
	return;
}

void mapCallback(void *data,int32_t result)
{
	PPB_ImageData *imageInterface = (PPB_ImageData *)sdlStore(NULL,GET_IMAGE_INTERFACE);
	struct mapCallbackData *readyData = (struct mapCallbackData *)data;
	if(readyData->screen == 0)
	{
		puts("DEBUG: mapCallback() 1");
		exit(1);
	}
	//DEBUG
	printf("DEBUG: mapCallback() - screen = %d\n",readyData->screen);
	
	void *pixels = imageInterface->Map(readyData->screen);
	if(pixels == 0)
	{
		puts("DEBUG: mapCallback() 2");
		exit(1);
	}
	sdlStore(pixels,SET_PIXELS);
	sem_post(readyData->sem);
	return;
}

void flushCallback(void *data,int32_t result)
{
	PPB_Graphics2D *g2DInterface = (PPB_Graphics2D *)sdlStore(NULL,GET_2D_INTERFACE);
	struct flushCallbackData *readyData = (struct flushCallbackData *)data;
	g2DInterface->Flush(readyData->screen,PP_BlockUntilComplete());
	sem_post(readyData->sem);
	return;
}
