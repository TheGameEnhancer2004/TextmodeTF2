#include "../SDK/SDK.h"

MAKE_HOOK(IMaterialSystem_SwapBuffers, U::Memory.GetVFunc(I::MaterialSystem, 40), void, // 40
		  void* rcx)
{
	return;
}

MAKE_HOOK(IMaterialSystem_FindMaterial, U::Memory.GetVFunc(I::MaterialSystem, 71), IMaterial*, // 71
		  void* rcx, char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix)
{
	if (SDK::BlacklistFile(pMaterialName))
	{
		return CALL_ORIGINAL(rcx, "debug/debugempty", pTextureGroupName, false, nullptr);
	}

	if (auto pMaterial = CALL_ORIGINAL(rcx, pMaterialName, pTextureGroupName, complain, pComplainPrefix))
	{
		return pMaterial;
	}

	return CALL_ORIGINAL(rcx, "debug/debugempty", pTextureGroupName, false, nullptr);
}

MAKE_HOOK(IMaterialSystem_FindTexture, U::Memory.GetVFunc(I::MaterialSystem, 79), ITexture*, // 79
		  void* rcx, char const* pTextureName, const char* pTextureGroupName, bool complain, int nAdditionalCreationFlags)
{
	if (SDK::BlacklistFile(pTextureName))
	{
		return CALL_ORIGINAL(rcx, "error", pTextureGroupName, false, nAdditionalCreationFlags);
	}

	if (auto pTexture = CALL_ORIGINAL(rcx, pTextureName, pTextureGroupName, complain, nAdditionalCreationFlags))
	{
		return pTexture;
	}

	return CALL_ORIGINAL(rcx, "error", pTextureGroupName, false, nAdditionalCreationFlags);
}

MAKE_HOOK(IMaterialSystem_CreateRenderTargetTexture, U::Memory.GetVFunc(I::MaterialSystem, 84), ITexture*, // 84
		  void* rcx, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat	format, MaterialRenderTargetDepth_t depth)
{
	// Use a minimal but valid 1x1 target to keep the engine happy while still
	// avoiding large memory allocations. Using 0 would cause shaderapidx9
	// to attempt to create a zero-sized texture which crashes in text-mode.
	// I've never had that crash btw
	return CALL_ORIGINAL(rcx, 1, 1, sizeMode, format, depth);
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx, U::Memory.GetVFunc(I::MaterialSystem, 85), ITexture*, // 85
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
	return CALL_ORIGINAL(rcx, pRTName, 1, 1, sizeMode, format, depth, textureFlags, renderTargetFlags);
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTexture, U::Memory.GetVFunc(I::MaterialSystem, 86), ITexture*, // 86
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, bool bClampTexCoords, bool bAutoMipMap)
{
	return CALL_ORIGINAL(rcx, pRTName, 1, 1, sizeMode, format, depth, bClampTexCoords, bAutoMipMap);
}

MAKE_HOOK(IMaterialSystem_CreateNamedRenderTargetTextureEx2, U::Memory.GetVFunc(I::MaterialSystem, 87), ITexture*, // 87
		  void* rcx, const char* pRTName, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags)
{
	return CALL_ORIGINAL(rcx, pRTName, 1, 1, sizeMode, format, depth, textureFlags, renderTargetFlags);
}
