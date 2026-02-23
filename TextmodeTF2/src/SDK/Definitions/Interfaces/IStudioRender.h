#pragma once
#include "Interface.h"
#include "../Misc/IAppSystem.h"

// Forward declarations
struct studiohdr_t;
struct studiohwdata_t;
struct Vector;
struct Vector4D;
struct Vector2D;
struct LightDesc_t;
struct Ray_t;
struct matrix3x4_t;
class IMaterial;
class IMesh;
struct IPooledVBAllocator;
class ITexture;
struct FlashlightState_t;
struct VMatrix;
struct vertexFileHeader_t;

typedef void* StudioDecalHandle_t;
#define STUDIORENDER_DECAL_INVALID ((StudioDecalHandle_t)0)

struct DrawModelResults_t;
struct DrawModelInfo_t;
struct GetTriangles_Output_t;
struct model_array_instance_t;

struct StudioRenderConfig_t
{
	float fEyeShiftX;
	float fEyeShiftY;
	float fEyeShiftZ;
	float fEyeSize;
	float fEyeGlintPixelWidthLODThreshold;
	int maxDecalsPerModel;
	int drawEntities;
	int skin;
	int fullbright;
	bool bEyeMove : 1;
	bool bSoftwareSkin : 1;
	bool bNoHardware : 1;
	bool bNoSoftware : 1;
	bool bTeeth : 1;
	bool bEyes : 1;
	bool bFlex : 1;
	bool bWireframe : 1;
	bool bDrawNormals : 1;
	bool bDrawTangentFrame : 1;
	bool bDrawZBufferedWireframe : 1;
	bool bSoftwareLighting : 1;
	bool bShowEnvCubemapOnly : 1;
	bool bWireframeDecals : 1;
	int m_nReserved[4];
};

enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};

class IStudioRender : public IAppSystem
{
public:
	virtual void BeginFrame(void) = 0;
	virtual void EndFrame(void) = 0;
	virtual void Mat_Stub(void* pMatSys) = 0;
	virtual void UpdateConfig(const StudioRenderConfig_t& config) = 0;
	virtual void GetCurrentConfig(StudioRenderConfig_t& config) = 0;
	virtual bool LoadModel(studiohdr_t* pStudioHdr, void* pVtxData, studiohwdata_t* pHardwareData) = 0;
	virtual void UnloadModel(studiohwdata_t* pHardwareData) = 0;
	virtual void RefreshStudioHdr(studiohdr_t* pStudioHdr, studiohwdata_t* pHardwareData) = 0;
	virtual void SetEyeViewTarget(const studiohdr_t* pStudioHdr, int nBodyIndex, const Vector& worldPosition) = 0;
	virtual int GetNumAmbientLightSamples() = 0;
	virtual const Vector* GetAmbientLightDirections() = 0;
	virtual void SetAmbientLightColors(const Vector4D* pAmbientOnlyColors) = 0;
	virtual void SetAmbientLightColors(const Vector* pAmbientOnlyColors) = 0;
	virtual void SetLocalLights(int numLights, const LightDesc_t* pLights) = 0;
	virtual void SetViewState(const Vector& viewOrigin, const Vector& viewRight, const Vector& viewUp, const Vector& viewPlaneNormal) = 0;
	virtual void LockFlexWeights(int nWeightCount, float** ppFlexWeights, float** ppFlexDelayedWeights = nullptr) = 0;
	virtual void UnlockFlexWeights() = 0;
	virtual matrix3x4_t* LockBoneMatrices(int nBoneCount) = 0;
	virtual void UnlockBoneMatrices() = 0;
	virtual int GetNumLODs(const studiohwdata_t& hardwareData) const = 0;
	virtual float GetLODSwitchValue(const studiohwdata_t& hardwareData, int lod) const = 0;
	virtual void SetLODSwitchValue(studiohwdata_t& hardwareData, int lod, float switchValue) = 0;
	virtual void SetColorModulation(float const* pColor) = 0;
	virtual void SetAlphaModulation(float flAlpha) = 0;
	
	// Index 29
	virtual void DrawModel(DrawModelResults_t* pResults, const DrawModelInfo_t& info, matrix3x4_t* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, const Vector& modelOrigin, int flags = 0) = 0;
	
	// Index 30
	virtual void DrawModelStaticProp(const DrawModelInfo_t& drawInfo, const matrix3x4_t& modelToWorld, int flags = 0) = 0;
	
	// Index 31
	virtual void DrawStaticPropDecals(const DrawModelInfo_t& drawInfo, const matrix3x4_t& modelToWorld) = 0;
	
	// Index 32
	virtual void DrawStaticPropShadows(const DrawModelInfo_t& drawInfo, const matrix3x4_t& modelToWorld, int flags) = 0;
	
	virtual void ForcedMaterialOverride(IMaterial* newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL) = 0;
	virtual StudioDecalHandle_t CreateDecalList(studiohwdata_t* pHardwareData) = 0;
	virtual void DestroyDecalList(StudioDecalHandle_t handle) = 0;
	virtual void AddDecal(StudioDecalHandle_t handle, studiohdr_t* pStudioHdr, matrix3x4_t* pBoneToWorld, const Ray_t& ray, const Vector& decalUp, IMaterial* pDecalMaterial, float radius, int body, bool noPokethru = false, int maxLODToDecal = -1) = 0;
	virtual void ComputeLighting(const Vector* pAmbient, int lightCount, LightDesc_t* pLights, const Vector& pt, const Vector& normal, Vector& lighting) = 0;
	virtual void ComputeLightingConstDirectional(const Vector* pAmbient, int lightCount, LightDesc_t* pLights, const Vector& pt, const Vector& normal, Vector& lighting, float flDirectionalAmount) = 0;
	virtual void AddShadow(IMaterial* pMaterial, void* pProxyData, FlashlightState_t* m_pFlashlightState = nullptr, VMatrix* pWorldToTexture = nullptr, ITexture* pFlashlightDepthTexture = nullptr) = 0;
	virtual void ClearAllShadows() = 0;
	virtual int ComputeModelLod(studiohwdata_t* pHardwareData, float unitSphereSize, float* pMetric = nullptr) = 0;
	virtual void GetPerfStats(DrawModelResults_t* pResults, const DrawModelInfo_t& info, void* pSpewBuf = nullptr) const = 0;
	virtual void GetTriangles(const DrawModelInfo_t& info, matrix3x4_t* pBoneToWorld, GetTriangles_Output_t& out) = 0;
	virtual int GetMaterialList(studiohdr_t* pStudioHdr, int count, IMaterial** ppMaterials) = 0;
	virtual int GetMaterialListFromBodyAndSkin(void* studio, int nSkin, int nBody, int nCountOutputMaterials, IMaterial** ppOutputMaterials) = 0;
	
	// Index 47 (approx)
	virtual void DrawModelArray(const DrawModelInfo_t& drawInfo, int arrayCount, model_array_instance_t* pInstanceData, int instanceStride, int flags = 0) = 0;
};
