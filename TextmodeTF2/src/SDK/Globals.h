#pragma once
#include "Definitions/Definitions.h"
#include "../Utils/Signatures/Signatures.h"
#include "../Utils/Memory/Memory.h"

#define TEXTMODE_LOG_FILE "TextmodeLog.log"
#define CONSOLE_LOG_FILE "Console.log"

namespace G
{
	inline std::string CurrentPath{};
	inline std::string AppdataPath{};
	inline uintptr_t CVideoModeCommon_SetupStartupGraphicAddr{};
	inline uintptr_t IFileSystemAddr{};
	inline uintptr_t IBaseFileSystemAddr{};
	inline uintptr_t g_bTextModeAddr{};
	inline uintptr_t g_bAllowSecureServersAddr{};
	inline uintptr_t Host_IsSecureServerAllowedAddr{};
	inline uintptr_t Client_CreateEntityByNameAddr{};
	inline uintptr_t Con_DebugLogAddr{};
	inline uintptr_t CParticleSystemMgr_DrawRenderCacheAddr{};
	inline uintptr_t CParticleCollection_SimulateAddr{};
	inline uintptr_t CStaticPropMgr_DrawStaticPropsAddr{};
	inline uintptr_t CStaticPropMgr_UnserializeStaticPropsAddr{};
	inline uintptr_t S_PrecacheSoundAddr{};
	inline uintptr_t CModelLoader_GetModelForNameAddr{};
	inline uintptr_t CModelRender_DrawModelExecuteAddr{};
	inline uintptr_t CDebugOverlay_AddBoxOverlayAddr{};
	inline uintptr_t CDebugOverlay_AddLineOverlayAddr{};
};