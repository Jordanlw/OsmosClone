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
#include "header/store.h"

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
	//DEBUG
	printf("DEBUG: didCreate() - value of instance is %d\n",instance);
	struct store *stored = malloc(sizeof(struct store));
	if(stored == 0)
	{
		puts("DEBUG: didCreate() - 1");
		exit(1);
	}
	storeFunc(stored);
	stored->didCreate = 1;
	stored->instance = instance;
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
	sleep(30);
	
	//DEBUG
	puts("DEBUG: entered PPP_InitializeModule().");
	
	struct store *stored = GET_STORE();
	//DEBUG
	puts("DEBUG: PPP_InitializeModule() - checkpoint 1");
	
	stored->coreInterface = (PPB_Core *)getBrowser(PPB_CORE_INTERFACE);
	//DEBUG
	puts("DEBUG: PPP_InitializeModule() - checkpoint 2");
	
	stored->g2DInterface = (PPB_Graphics2D *)getBrowser(PPB_GRAPHICS_2D_INTERFACE);
	
	stored->instanceInterface = (PPB_Instance *)getBrowser(PPB_INSTANCE_INTERFACE);
	//DEBUG
	puts("DEBUG: PPP_InitializeModule() - checkpoint 3");
	
	stored->imageInterface = (PPB_ImageData *)getBrowser(PPB_IMAGEDATA_INTERFACE);
	
	stored->inputInterface = (PPB_InputEvent *)getBrowser(PPB_INPUT_EVENT_INTERFACE);
	
	stored->mouseInterface = (PPB_MouseInputEvent *)getBrowser(PPB_MOUSE_INPUT_EVENT_INTERFACE);
	//DEBUG
	puts("DEBUG: PPP_InitializeModule() - checkpoint 4");
	
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
