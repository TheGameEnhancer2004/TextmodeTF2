#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// void CDebugOverlay::AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration)
MAKE_HOOK(CDebugOverlay_AddLineOverlay, G::CDebugOverlay_AddLineOverlayAddr, void, void* rcx, const void* origin, const void* dest, int r, int g, int b, bool noDepthTest, float duration)
{
	return;
}
