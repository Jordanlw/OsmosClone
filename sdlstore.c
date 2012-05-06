#include <ppapi/c/pp_instance.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/pp_rect.h>

#include "header/main.h"
#include "header/sdlstore.h"

void *sdlStore(void *data,int option)
{
	static PP_Resource screen = 0;
	static struct PP_Rect *camera = 0;
	static int player = 0;
	static double frameTime = 0;
	static struct bgData *background = 0;
	static int *bgSizes = 0;
	static int selObj = 0;
	static void *coreInterface = 0;
	static void *g2DInterface = 0;
	static PP_Instance naclInstance = 0;
	static void *instanceInterface = 0;
	static void *imageInterface = 0;
	static void *inputInterface = 0;
	static void *mouseInterface = 0;
	static void *pixels = 0;
	static void *mousePos = 0;
	//DEBUG
	//printf("store: %p\n",bgSizes);
	
	if(option)
	{
		switch(option)
		{
			case SET_CAMERA:camera = (struct PP_Rect *)data;break;
			case SET_SCREEN:screen = *(PP_Resource *)data;break;
			case GET_CAMERA:return (void *)camera;break;
			case GET_SCREEN:return (void *)&screen;break;
			case SET_PLAYER:player = *(int *)data;break;
			case GET_PLAYER:return (void *)&player;break;
			case SET_FRAMETIME:frameTime = *(double *)data;break;
			case GET_FRAMETIME:return &frameTime;break;
			case SET_BACKGROUND: background = (struct bgData *)data;break;
			case GET_BACKGROUND: return (void *)background;break;
			case SET_BG_SIZE: bgSizes = (int *)data;break;
			case GET_BG_SIZE: return (void *)bgSizes;break;
			case GET_SELECTED_OBJECT: return (void *)&selObj;break;
			case SET_SELECTED_OBJECT: selObj = *(int *)data;break;
			case GET_CORE_INTERFACE: return coreInterface;break;
			case SET_CORE_INTERFACE: coreInterface = data;break;
			case SET_NACL_INSTANCE: naclInstance = *(PP_Instance *)data;break;
			case GET_NACL_INSTANCE: return (void *)naclInstance;break;
			case SET_2D_INTERFACE: g2DInterface = data;break;
			case GET_2D_INTERFACE: return g2DInterface;break; 
			case SET_INSTANCE_INTERFACE: instanceInterface = data;break;
			case GET_INSTANCE_INTERFACE: return instanceInterface;break;
			case SET_IMAGE_INTERFACE: imageInterface = data;break;
			case GET_IMAGE_INTERFACE: return imageInterface;break;
			case SET_PIXELS: pixels = data;break;
			case GET_PIXELS: return pixels;break;
			case SET_INPUT_INTERFACE: inputInterface = data;break;
			case GET_INPUT_INTERFACE: return data;break;
			case GET_MOUSE_INTERFACE: return data;break;
			case SET_MOUSE_INTERFACE: mouseInterface = data;break;
			case SET_MOUSE_POS: mousePos = data;break;
			case GET_MOUSE_POS: return mousePos;break;
			default: puts("DEBUG: sdlStore() 1"); return (void *)0;break;
		}
	}
	else
	{
		puts("DEBUG: sdlStore() 2");
		return (void *)0;
	}
	//DEBUG
	//printf("selObj %d player %d\n",selObj,player);
	
	return 0;
}
