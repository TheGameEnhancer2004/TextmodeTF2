#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

MAKE_HOOK(CEngineSoundClient_EmitSoundInternal, G::CEngineSoundClient_EmitSoundInternalAddr, void, void* rcx, void* rdx, void* r8, void* r9, void* pSample, float flVolume, int iSoundLevel, int iFlags, int iPitch, int iSpecialDSP, void *pOrigin, void *pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity)
{
	return;
}
