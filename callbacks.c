#include <unistd.h>
#include <ppapi/c/ppb_input_event.h>
#include <ppapi/c/pp_errors.h>
#include <ppapi/c/ppb_graphics_2d.h>
#include <ppapi/c/pp_resource.h>

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
	}
	else if(returnValue == PP_ERROR_NOTSUPPORTED)
	{
		puts("DEBUG: inputCallback() 2");
	}
	return;
}

void g2DCallback(void *data,int32_t result)
{
	struct PPB_Graphics2D *g2DInterface = (struct PPB_Graphics2D *)sdlStore(NULL,GET_2D_INTERFACE);
	struct g2DCallbackData *readyData = (struct g2DCallbackData *)data;
	PP_Resource screen = g2DInterface->Create(readyData->instance,readyData->size,readyData->flag);
	sdlStore((void *)&screen,SET_SCREEN);
	return;
}
