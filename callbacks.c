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
	struct store *stored = GET_STORE();
	struct inputCallbackData *readyData = (struct inputCallbackData *)data;
	if(stored->instance == 0)
	{
		puts("DEBUG: inputCallback() 3");
		exit(1);
	}
	int32_t returnValue = stored->inputInterface->RequestInputEvents(stored->instance,readyData->flags);
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
	return;
}

void g2DCallback(void *data,int32_t result)
{
	struct store *stored = GET_STORE();
	struct g2DCallbackData *readyData = (struct g2DCallbackData *)data;
	if(stored->instance == 0)
	{
		puts("DEBUG: g2DCallback() 2");
		exit(1);
	}
	//DEBUG
	printf("DEBUG: g2DCallback() - width = %d - height = %d - instance = %d\n",readyData->width,readyData->height,stored->instance);
	
	stored->screen = stored->g2DInterface->Create(stored->instance,&(struct PP_Size){readyData->width,readyData->height},readyData->flag);
	//DEBUG
	printf("DEBUG: g2DCallback() - screen = %d\n",stored->screen);
	
	if(stored->screen == 0)
	{
		puts("DEBUG: g2DCallback() 1");
		exit(1);
	}
	return;
}

void bindCallback(void *data,int32_t result)
{
	struct store *stored = GET_STORE();
	struct bindCallbackData *readyData = (struct bindCallbackData *)data;
	if(stored->g2DInterface->IsGraphics2D(readyData->screen) != PP_TRUE)
	{
		puts("DEBUG: bindCallback() 1");
		exit(1);
	}
	if(stored->instance == 0)
	{
		puts("DEBUG: bindCallback() 2");
		exit(1);
	}
	if(stored->instanceInterface->BindGraphics(stored->instance,readyData->screen) == PP_FALSE)
	{
		puts("DEBUG: bindCallback() 3");
		exit(1);
	}
	return;
}

void timeCallback(void *data,int32_t result)
{
	struct timeCallbackData *readyData = (struct timeCallbackData *)data;
	struct store *stored = GET_STORE();
	*(readyData->ticks) = stored->coreInterface->GetTimeTicks();
	sem_post(readyData->sem);
	return;
}

void mapCallback(void *data,int32_t result)
{
	struct store *stored = GET_STORE();
	struct mapCallbackData *readyData = (struct mapCallbackData *)data;
	//DEBUG
	printf("DEBUG: mapCallback() - image = %d\n",readyData->image);
	if(stored->imageInterface->IsImageData(readyData->image) != PP_TRUE)
	{
		puts("DEBUG: mapCallback() 1");
		exit(1);
	}
	stored->pixels = stored->imageInterface->Map(readyData->image);
	if(stored->pixels == 0)
	{
		puts("DEBUG: mapCallback() 2");
		exit(1);
	}
	return;
}

void flushCallback(void *data,int32_t result)
{
	struct store *stored = GET_STORE();
	struct flushCallbackData *readyData = (struct flushCallbackData *)data;
	stored->g2DInterface->Flush(readyData->screen,PP_BlockUntilComplete());
	return;
}

void imageCallback(void *data,int32_t result)
{
	struct store *stored = GET_STORE();
	if(stored->instance == 0)
	{
		puts("DEBUG: imageCallback() 1");
		exit(1);
	}
	struct imageCallbackData *readyData = (struct imageCallbackData *)data;
	stored->image = stored->imageInterface->Create(stored->instance,stored->imageInterface->GetNativeImageDataFormat(),&(readyData->size),readyData->flag);
	return;
}
