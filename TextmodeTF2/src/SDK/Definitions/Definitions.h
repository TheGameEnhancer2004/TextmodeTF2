#pragma once
#include <string>

typedef int FileFindHandle_t;

//---------------------------------------------------------
// Async file status
//---------------------------------------------------------
enum FSAsyncStatus_t
{
	FSASYNC_ERR_NOT_MINE     = -8,	// Filename not part of the specified file system, try a different one.  (Used internally to find the right filesystem)
	FSASYNC_ERR_RETRY_LATER  = -7,	// Failure for a reason that might be temporary.  You might retry, but not immediately.  (E.g. Network problems)
	FSASYNC_ERR_ALIGNMENT    = -6,	// read parameters invalid for unbuffered IO
	FSASYNC_ERR_FAILURE      = -5,	// hard subsystem failure
	FSASYNC_ERR_READING      = -4,	// read error on file
	FSASYNC_ERR_NOMEMORY     = -3,	// out of memory for file read
	FSASYNC_ERR_UNKNOWNID    = -2,	// caller's provided id is not recognized
	FSASYNC_ERR_FILEOPEN     = -1,	// filename could not be opened (bad path, not exist, etc)
	FSASYNC_OK               = 0,	// operation is successful
	FSASYNC_STATUS_PENDING,			// file is properly queued, waiting for service
	FSASYNC_STATUS_INPROGRESS,		// file is being accessed
	FSASYNC_STATUS_ABORTED,			// file was aborted by caller
	FSASYNC_STATUS_UNSERVICED,		// file is not yet queued
};
//-----------------------------------------------------------------------------
// File system allocation functions. Client must free on failure
//-----------------------------------------------------------------------------
typedef void *(*FSAllocFunc_t)( const char *pszFilename, unsigned nBytes );

#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
DECLARE_POINTER_HANDLE(FSAsyncControl_t);
DECLARE_POINTER_HANDLE(FSAsyncFile_t);
const FSAsyncFile_t FS_INVALID_ASYNC_FILE = (FSAsyncFile_t)(0x0000ffff);

//---------------------------------------------------------
// Optional completion callback for each async file serviced (or failed)
// call is not reentrant, async i/o guaranteed suspended until return
// Note: If you change the signature of the callback, you will have to account for it in FileSystemV12 (toml [4/18/2005] )
//---------------------------------------------------------
struct FileAsyncRequest_t;
typedef void (*FSAsyncCallbackFunc_t)(const FileAsyncRequest_t &request, int nBytesRead, FSAsyncStatus_t err);

//---------------------------------------------------------
// Description of an async request
//---------------------------------------------------------
struct FileAsyncRequest_t
{
	FileAsyncRequest_t()	{ memset( this, 0, sizeof(*this) ); hSpecificAsyncFile = FS_INVALID_ASYNC_FILE;	}
	const char *			pszFilename;		// file system name
	void *					pData;				// optional, system will alloc/free if NULL
	int						nOffset;			// optional initial seek_set, 0=beginning
	int						nBytes;				// optional read clamp, -1=exist test, 0=full read
	FSAsyncCallbackFunc_t	pfnCallback;		// optional completion callback
	void *					pContext;			// caller's unique file identifier
	int						priority;			// inter list priority, 0=lowest
	unsigned				flags;				// behavior modifier
	const char *			pszPathID;			// path ID (NOTE: this field is here to remain binary compatible with release HL2 filesystem interface)
	FSAsyncFile_t			hSpecificAsyncFile; // Optional hint obtained using AsyncBeginRead()
	FSAllocFunc_t			pfnAlloc;			// custom allocator. can be null. not compatible with FSASYNC_FLAGS_FREEDATAPTR
};

typedef void * FileHandle_t;
typedef void * FileCacheHandle_t;

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

typedef unsigned int VPANEL;