#include "../SDK/SDK.h"

MAKE_HOOK(IMaterialSystem_SwapBuffers, U::Memory.GetVFunc(I::MaterialSystem, 40), void, // 40
		  void* rcx)
{
	return;
}

MAKE_HOOK(IMaterialSystem_CreateRenderTargetTexture, U::Memory.GetVFunc(I::MaterialSystem, 84), ITexture*, // 84
		  void* rcx, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat	format, MaterialRenderTargetDepth_t depth)
{
	return CALL_ORIGINAL(rcx, 0, 0, sizeMode, format, depth);
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx, U::Memory.GetVFunc(I::MaterialSystem, 85), ITexture*, // 85
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
	return CALL_ORIGINAL(rcx, pRTName, 0, 0, sizeMode, format, depth, textureFlags, renderTargetFlags);
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTexture, U::Memory.GetVFunc(I::MaterialSystem, 86), ITexture*, // 86
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, bool bClampTexCoords, bool bAutoMipMap)
{
	return CALL_ORIGINAL(rcx, pRTName, 0, 0, sizeMode, format, depth, bClampTexCoords, bAutoMipMap);
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx2, U::Memory.GetVFunc(I::MaterialSystem, 87), ITexture*, // 87
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
	return CALL_ORIGINAL(rcx, pRTName, 0, 0, sizeMode, format, depth, textureFlags, renderTargetFlags);
}
