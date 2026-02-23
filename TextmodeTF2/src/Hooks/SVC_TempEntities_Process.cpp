#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

MAKE_HOOK(SVC_TempEntities_Process, G::SVC_TempEntities_ProcessAddr, bool, void* rcx)
{
	return true;
}
