#include <unistd.h>
#include <ppapi/c/pp_bool.h>
#include <ppapi/c/pp_instance.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/ppb_input_event.h>

#include "header/store.h"
#include "header/main.h"

PP_Bool HandleInputEvent(PP_Instance instance,PP_Resource inputEvent)
{
	struct store *stored = GET_STORE();
	PP_InputEvent_Type type = stored->inputInterface->GetType(inputEvent);
	switch(type)
	{
		case PP_INPUTEVENT_TYPE_MOUSEMOVE:
		{
			stored->mousePos = stored->mouseInterface->GetPosition(inputEvent);
			break;
		}
		case PP_INPUTEVENT_TYPE_MOUSEDOWN:
		{
			PP_InputEvent_MouseButton mouseButton = stored->mouseInterface->GetButton(inputEvent);
			if(mouseButton == PP_INPUTEVENT_MOUSEBUTTON_LEFT)
			{
				movePlayerStore(1,SET_PLAYER_STORE_MOUSE_DOWN);
			}
			break;
		}
		case PP_INPUTEVENT_TYPE_MOUSEUP:
		{
			PP_InputEvent_MouseButton mouseButton = stored->mouseInterface->GetButton(inputEvent);
			if(mouseButton == PP_INPUTEVENT_MOUSEBUTTON_LEFT)
			{
				movePlayerStore(0,SET_PLAYER_STORE_MOUSE_DOWN);
			}
			break;
		}
	}
}
