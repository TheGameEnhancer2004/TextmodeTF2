#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

MAKE_HOOK(SVC_GameEvent_Process, G::SVC_GameEvent_ProcessAddr, bool, void* rcx)
{
	return true;
}
