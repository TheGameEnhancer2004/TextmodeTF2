#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

MAKE_HOOK(CShadowMgr_RenderShadows, G::CShadowMgr_RenderShadowsAddr, void, void* rcx, void* rdx, void* r8, void* r9)
{
	return;
}
