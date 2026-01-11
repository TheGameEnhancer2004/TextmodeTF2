#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// CParticleSystemMgr::DrawRenderCache(bool bInclusionMode)
MAKE_HOOK(CParticleSystemMgr_DrawRenderCache, G::CParticleSystemMgr_DrawRenderCacheAddr, void, void* rcx, bool bInclusionMode)
{
	return;
}
