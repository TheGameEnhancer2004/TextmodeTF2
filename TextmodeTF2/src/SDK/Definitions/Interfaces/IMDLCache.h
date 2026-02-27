#pragma once
#include "Interface.h"
#include "../Misc/IAppSystem.h"

typedef unsigned short MDLHandle_t;

enum MDLCacheDataType_t
{
	MDLCACHE_STUDIOHDR = 0,
	MDLCACHE_STUDIOHWDATA,
	MDLCACHE_VCOLLIDE,
	MDLCACHE_ANIMBLOCK,
	MDLCACHE_VIRTUALMODEL,
	MDLCACHE_VERTEXES,
	MDLCACHE_DECODEDANIMBLOCK,
};

class IMDLCacheNotify
{
public:
	virtual void OnDataLoaded(MDLCacheDataType_t type, MDLHandle_t handle) = 0;
	virtual void OnDataUnloaded(MDLCacheDataType_t type, MDLHandle_t handle) = 0;
};

class IMDLCache : public IAppSystem
{
public:
	virtual void SetCacheNotify(IMDLCacheNotify* pNotify) = 0;
	virtual MDLHandle_t FindMDL(const char* pMDLRelativePath) = 0;
	virtual int AddRef(MDLHandle_t handle) = 0;
	virtual int Release(MDLHandle_t handle) = 0;
	virtual int GetRef(MDLHandle_t handle) = 0;
	virtual void* GetStudioHdr(MDLHandle_t handle) = 0;
	virtual void* GetHardwareData(MDLHandle_t handle) = 0;
	virtual void* GetVCollide(MDLHandle_t handle) = 0;
	virtual unsigned char* GetAnimBlock(MDLHandle_t handle, int nBlock) = 0;
	virtual void* GetVirtualModel(MDLHandle_t handle) = 0;
	virtual int GetAutoplayList(MDLHandle_t handle, unsigned short** pOut) = 0;
	virtual void* GetVertexData(MDLHandle_t handle) = 0;
	virtual void TouchAllData_Old(MDLHandle_t handle) = 0;
	virtual void SetUserData(MDLHandle_t handle, void* pData) = 0;
	virtual void* GetUserData(MDLHandle_t handle) = 0;
	virtual bool IsErrorModel(MDLHandle_t handle) = 0;
	virtual void Flush(int nFlushFlags = 0xFFFFFFFF) = 0;
	virtual void Flush(MDLHandle_t handle, int nFlushFlags = 0xFFFFFFFF) = 0;
	virtual const char* GetModelName(MDLHandle_t handle) = 0;
	virtual void* GetVirtualModelFast(const void* pStudioHdr, MDLHandle_t handle) = 0;
	virtual void BeginLock() = 0;
	virtual void EndLock() = 0;
	virtual int* GetFrameUnlockCounterPtrOLD() = 0;
	virtual void FinishPendingLoads() = 0;
	virtual void* GetVCollideEx(MDLHandle_t handle, bool synchronousLoad = true) = 0;
	virtual bool GetVCollideSize(MDLHandle_t handle, int* pVCollideSize) = 0;
	virtual bool GetAsyncLoad(MDLCacheDataType_t type) = 0;
	virtual bool SetAsyncLoad(MDLCacheDataType_t type, bool bAsync) = 0;
	virtual void BeginMapLoad() = 0;
	virtual void EndMapLoad() = 0;
	virtual void MarkAsLoaded(MDLHandle_t handle) = 0;
	virtual void InitPreloadData(bool rebuild) = 0;
	virtual void ShutdownPreloadData() = 0;
	virtual bool IsDataLoaded(MDLHandle_t handle, MDLCacheDataType_t type) = 0;
	virtual int* GetFrameUnlockCounterPtr(MDLCacheDataType_t type) = 0;
	virtual void* LockStudioHdr(MDLHandle_t handle) = 0;
	virtual void UnlockStudioHdr(MDLHandle_t handle) = 0;
	virtual bool PreloadModel(MDLHandle_t handle) = 0;
	virtual void ResetErrorModelStatus(MDLHandle_t handle) = 0;
	virtual void MarkFrame() = 0;
	virtual bool TouchAllData(MDLHandle_t handle) = 0;
};
