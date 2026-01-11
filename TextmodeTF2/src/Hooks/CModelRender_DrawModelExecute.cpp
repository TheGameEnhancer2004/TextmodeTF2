#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// void CModelRender::DrawModelExecute( const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld )
MAKE_HOOK(CModelRender_DrawModelExecute, G::CModelRender_DrawModelExecuteAddr, void, void* rcx, void* state, void* pInfo, void* pCustomBoneToWorld)
{
	return;
}
