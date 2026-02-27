#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// void IPanel::PaintTraverse(VPANEL vguiPanel, bool forceRepaint, bool allowForce)
MAKE_HOOK(IPanel_PaintTraverse, G::IPanel_PaintTraverseAddr, void, void* rcx, VPANEL vguiPanel, bool forceRepaint, bool allowForce)
{
	return;
}
