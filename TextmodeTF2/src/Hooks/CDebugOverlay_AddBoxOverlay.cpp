#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// void CDebugOverlay::AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration)
MAKE_HOOK(CDebugOverlay_AddBoxOverlay, G::CDebugOverlay_AddBoxOverlayAddr, void, void* rcx, const void* origin, const void* mins, const void* max, const void* orientation, int r, int g, int b, int a, float duration)
{
	return;
}
