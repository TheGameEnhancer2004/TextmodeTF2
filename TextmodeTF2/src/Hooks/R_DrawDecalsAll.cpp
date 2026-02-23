#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

MAKE_HOOK(R_DrawDecalsAll, G::R_DrawDecalsAllAddr, void, void* rcx, void* rdx, void* r8, void* r9)
{
	return;
}
