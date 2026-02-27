#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"
#include "../SDK/Definitions/Interfaces/IStudioRender.h"

// void IStudioRender::DrawModel(DrawModelResults_t *pResults, const DrawModelInfo_t& info, matrix3x4_t *pBoneToWorld, float *pFlexWeights, float *pFlexDelayedWeights, const Vector &modelOrigin, int flags)
MAKE_HOOK(IStudioRender_DrawModel, G::IStudioRender_DrawModelAddr, void, void* rcx, void* pResults, void* info, void* pBoneToWorld, void* pFlexWeights, void* pFlexDelayedWeights, void* modelOrigin, int flags)
{
	return;
}

// void IStudioRender::DrawModelStaticProp(const DrawModelInfo_t& drawInfo, const matrix3x4_t &modelToWorld, int flags)
MAKE_HOOK(IStudioRender_DrawModelStaticProp, G::IStudioRender_DrawModelStaticPropAddr, void, void* rcx, void* drawInfo, void* modelToWorld, int flags)
{
	return;
}

// void IStudioRender::DrawStaticPropDecals(const DrawModelInfo_t &drawInfo, const matrix3x4_t &modelToWorld)
MAKE_HOOK(IStudioRender_DrawStaticPropDecals, G::IStudioRender_DrawStaticPropDecalsAddr, void, void* rcx, void* drawInfo, void* modelToWorld)
{
	return;
}

// void IStudioRender::DrawStaticPropShadows(const DrawModelInfo_t &drawInfo, const matrix3x4_t &modelToWorld, int flags)
MAKE_HOOK(IStudioRender_DrawStaticPropShadows, G::IStudioRender_DrawStaticPropShadowsAddr, void, void* rcx, void* drawInfo, void* modelToWorld, int flags)
{
	return;
}

// void IStudioRender::AddDecal(StudioDecalHandle_t handle, studiohdr_t *pStudioHdr, matrix3x4_t *pBoneToWorld, const Ray_t & ray, const Vector& decalUp, IMaterial* pDecalMaterial, float radius, int body, bool noPokethru, int maxLODToDecal)
MAKE_HOOK(IStudioRender_AddDecal, G::IStudioRender_AddDecalAddr, void, void* rcx, void* handle, void* pStudioHdr, void* pBoneToWorld, void* ray, void* decalUp, void* pDecalMaterial, float radius, int body, bool noPokethru, int maxLODToDecal)
{
	return;
}

// void IStudioRender::AddShadow(IMaterial* pMaterial, void* pProxyData, FlashlightState_t *m_pFlashlightState, VMatrix *pWorldToTexture, ITexture *pFlashlightDepthTexture)
MAKE_HOOK(IStudioRender_AddShadow, G::IStudioRender_AddShadowAddr, void, void* rcx, void* pMaterial, void* pProxyData, void* m_pFlashlightState, void* pWorldToTexture, void* pFlashlightDepthTexture)
{
	return;
}

// void IStudioRender::DrawModelArray(const DrawModelInfo_t &drawInfo, int arrayCount, model_array_instance_t *pInstanceData, int instanceStride, int flags)
MAKE_HOOK(IStudioRender_DrawModelArray, G::IStudioRender_DrawModelArrayAddr, void, void* rcx, void* drawInfo, int arrayCount, void* pInstanceData, int instanceStride, int flags)
{
	return;
}
