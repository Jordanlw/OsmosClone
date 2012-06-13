#include <ppapi/c/pp_instance.h>
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/pp_rect.h>

#include "header/main.h"
#include "header/store.h"

struct store *storeFunc(struct store *storeInput)
{
	static struct store *stored = 0;
	if(storeInput != 0)
	{
		stored = storeInput;
	}
	return stored;
}
