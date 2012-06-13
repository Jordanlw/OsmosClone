#include <ppapi/c/pp_resource.h>
#include <ppapi/c/pp_instance.h>
#include <ppapi/c/pp_rect.h>
#include <ppapi/c/ppb_core.h>
#include <ppapi/c/ppb_graphics_2d.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppb_image_data.h>
#include <ppapi/c/ppb_input_event.h>
#include <ppapi/c/pp_bool.h>
#include <ppapi/c/pp_point.h>

#include "main.h"
#include "background.h"

#define GET_STORE() (storeFunc(0))

struct store
{
	PP_Resource screen;
	PP_Resource image;
	struct PP_Rect camera;
	int player;
	double frameTime;
	struct bgData *background;
	int *bgSizes;
	int selObj;
	PP_Instance instance;
	PPB_Core *coreInterface;
	PPB_Graphics2D *g2DInterface;
	PPB_Instance *instanceInterface;
	PPB_ImageData *imageInterface;
	PPB_InputEvent *inputInterface;
	PPB_MouseInputEvent *mouseInterface;
	void *pixels;
	PP_Bool didCreate;
	struct PP_Point mousePos;
	
};

struct store *storeFunc(struct store *);
