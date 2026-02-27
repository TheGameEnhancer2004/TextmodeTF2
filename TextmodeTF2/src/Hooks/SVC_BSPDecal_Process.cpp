#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

MAKE_HOOK(SVC_BSPDecal_Process, G::SVC_BSPDecal_ProcessAddr, bool, void* rcx)
{
	return true;
}
