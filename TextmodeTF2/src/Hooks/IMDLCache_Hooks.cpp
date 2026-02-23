#include "../SDK/SDK.h"

MAKE_HOOK(IMDLCache_GetHardwareData, U::Memory.FindSignature("datacache.dll", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B 05 ? ? ? ?"), void*,
		  void* rcx, MDLHandle_t handle)
{
	return nullptr;
}

MAKE_HOOK(IMDLCache_GetVertexData, U::Memory.FindSignature("datacache.dll", "48 83 EC 28 48 8B 05 ? ? ? ? 83 78 58 00"), void*,
		  void* rcx, MDLHandle_t handle)
{
	return nullptr;
}

MAKE_HOOK(IMDLCache_TouchAllData, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IMDLCache), 45), bool,
		  void* rcx, MDLHandle_t handle)
{
	return true;
}
