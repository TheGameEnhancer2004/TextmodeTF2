#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// void CStaticPropMgr::DrawStaticProps( IClientRenderable **pProps, int count, bool bShadowDepth, bool drawVCollideWireframe )
MAKE_HOOK(CStaticPropMgr_DrawStaticProps, G::CStaticPropMgr_DrawStaticPropsAddr, void, void* rcx, void* pProps, int count, bool bShadowDepth, bool drawVCollideWireframe)
{
	return;
}
