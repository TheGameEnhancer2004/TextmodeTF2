#include "../SDK/SDK.h"

MAKE_HOOK(IMDLCache_ProcessDataIntoCache, U::Memory.GetVFunc(reinterpret_cast<void*>(G::IMDLCache), 33), bool,
		  void* rcx, MDLHandle_t handle, MDLCacheDataType_t type, void* pData, int nDataSize, bool bAsync)
{
	if (type == MDLCACHE_VERTEXES || type == MDLCACHE_STUDIOHWDATA)
		return true;

	return CALL_ORIGINAL(rcx, handle, type, pData, nDataSize, bAsync);
}
