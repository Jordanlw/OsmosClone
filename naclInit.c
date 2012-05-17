#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <ppapi/c/ppp.h>
#include <ppapi/c/ppb.h>
#include <ppapi/c/pp_errors.h>
#include <ppapi/c/pp_instance.h>
#include <ppapi/c/pp_bool.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/ppp_instance.h>
#include <ppapi/c/ppb_core.h>
#include <ppapi/c/ppb_graphics_2d.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppb_image_data.h>
#include <ppapi/c/ppb_input_event.h>

#include "header/main.h"

void didChangeFocus(PP_Instance instance, PP_Bool hasFocus)
{
	return;
}

void didChangeView(PP_Instance instance, PP_Resource viewResource)
{
	return;
}

PP_Bool didCreate(PP_Instance instance, uint32_t argc, const char **argn, const char **argv)
{
	sdlStore((void *)&instance,SET_NACL_INSTANCE);
	return PP_TRUE;
}

void didDestroy(PP_Instance instance)
{
	return;
}

PP_Bool handleDocumentLoad(PP_Instance instance, PP_Resource urlLoader)
{
	return PP_FALSE;
}

const void *PPP_GetInterface(const char *interfaceName)
{
	if(strcmp(interfaceName,PPP_INSTANCE_INTERFACE) == 0)
	{
		static PPP_Instance instanceInterface = 
		{
			&didCreate,
			&didDestroy,
			&didChangeView,
			&didChangeFocus,
			&handleDocumentLoad,
		};
		return (void *)&instanceInterface;
	}
	return NULL;
}

int32_t PPP_InitializeModule(PP_Module moduleId, PPB_GetInterface getBrowser)
{
	//DEBUG
	puts("DEBUG: entered PPP_InitializeModule().");
	//sleep(15);
	
	PPB_Core *coreInterface = (PPB_Core *)getBrowser(PPB_CORE_INTERFACE);
	sdlStore((void *)coreInterface,SET_CORE_INTERFACE);
	
	PPB_Graphics2D *g2DInterface = (PPB_Graphics2D *)getBrowser(PPB_GRAPHICS_2D_INTERFACE);
	sdlStore((void *)g2DInterface,SET_2D_INTERFACE);
	
	PPB_Instance *instanceInterface = (PPB_Instance *)getBrowser(PPB_INSTANCE_INTERFACE);
	sdlStore((void *)instanceInterface,SET_INSTANCE_INTERFACE);
	
	PPB_ImageData *imageInterface = (PPB_ImageData *)getBrowser(PPB_IMAGEDATA_INTERFACE);
	sdlStore((void *)imageInterface,SET_IMAGE_INTERFACE);
	
	PPB_InputEvent *inputInterface = (PPB_InputEvent *)getBrowser(PPB_INPUT_EVENT_INTERFACE);
	sdlStore((void *)inputInterface,SET_INPUT_INTERFACE);
	//DEBUG
	printf("DEBUG: value inputInterface is %p in PPP_InitializeModule()\n",inputInterface);
	
	PPB_MouseInputEvent *mouseInterface = (PPB_MouseInputEvent *)getBrowser(PPB_MOUSE_INPUT_EVENT_INTERFACE);
	sdlStore((void *)mouseInterface,SET_MOUSE_INTERFACE);
	
	pthread_t *thread = (pthread_t *)malloc(sizeof(pthread_t));
	pthread_create(thread,NULL,gameMain,NULL);
	//DEBUG
	puts("DEBUG: left PPP_InitializeModule().");
	
	return PP_OK;
}

void PPP_ShutdownModule()
{
	return;
}
