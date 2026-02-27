#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

MAKE_HOOK(SVC_Sounds_Process, G::SVC_Sounds_ProcessAddr, bool, void* rcx)
{
	return true;
}
