#pragma once
#include "Interface.h"
#include "../Misc/IAppSystem.h"

//-----------------------------------------------------------------------------
// enums used when dealing with video services
//-----------------------------------------------------------------------------

namespace VideoResult
{
	enum EVideoResult_t
	{
		SUCCESS = 0,

		SYSTEM_NOT_AVAILABLE,
		CODEC_NOT_AVAILABLE,
		FEATURE_NOT_AVAILABLE,

		UNKNOWN_OPERATION,
		ILLEGAL_OPERATION,
		OPERATION_NOT_SUPPORTED,

		BAD_INPUT_PARAMETERS,
		OPERATION_ALREADY_PERFORMED,
		OPERATION_OUT_OF_SEQUENCE,

		VIDEO_ERROR_OCCURED,
		FILE_ERROR_OCCURED,
		AUDIO_ERROR_OCCURED,
		SYSTEM_ERROR_OCCURED,
		INITIALIZATION_ERROR_OCCURED,
		SHUTDOWN_ERROR_OCCURED,

		MATERIAL_NOT_FOUND,
		RECORDER_NOT_FOUND,
		VIDEO_FILE_NOT_FOUND,
		VIDEO_SYSTEM_NOT_FOUND,
	};
};
typedef VideoResult::EVideoResult_t VideoResult_t;

namespace VideoSystem
{
	enum EVideoSystem_t
	{
		ALL_VIDEO_SYSTEMS = -2,
		DETERMINE_FROM_FILE_EXTENSION = -1,
		NONE = 0,

		BINK,
	};
}
typedef VideoSystem::EVideoSystem_t VideoSystem_t;

typedef int VideoSystemStatus_t;
typedef int VideoSystemFeature_t;
typedef int VideoEncodeCodec_t;
typedef int VideoPlaybackFlags_t;
typedef int VideoSoundDeviceOperation_t;

class IVideoMaterial;
class IVideoRecorder;

//-----------------------------------------------------------------------------
// Main VIDEO_SERVICES interface
//-----------------------------------------------------------------------------
#define VIDEO_SERVICES_INTERFACE_VERSION	"IVideoServices002"


class IVideoServices : public IAppSystem
{
public:
	// Query the available video systems
	virtual int						GetAvailableVideoSystemCount() = 0;
	virtual VideoSystem_t			GetAvailableVideoSystem(int n) = 0;

	virtual bool					IsVideoSystemAvailable(VideoSystem_t videoSystem) = 0;
	virtual VideoSystemStatus_t		GetVideoSystemStatus(VideoSystem_t videoSystem) = 0;
	virtual VideoSystemFeature_t	GetVideoSystemFeatures(VideoSystem_t videoSystem) = 0;
	virtual const char*				GetVideoSystemName(VideoSystem_t videoSystem) = 0;

	virtual VideoSystem_t			FindNextSystemWithFeature(VideoSystemFeature_t features, VideoSystem_t startAfter = VideoSystem::NONE) = 0;

	virtual VideoResult_t			GetLastResult() = 0;

	// deal with video file extensions and video system mappings
	virtual	int						GetSupportedFileExtensionCount(VideoSystem_t videoSystem) = 0;
	virtual const char*				GetSupportedFileExtension(VideoSystem_t videoSystem, int extNum = 0) = 0;
	virtual VideoSystemFeature_t    GetSupportedFileExtensionFeatures(VideoSystem_t videoSystem, int extNum = 0) = 0;

	virtual	VideoSystem_t			LocateVideoSystemForPlayingFile(const char* pFileName, VideoSystemFeature_t playMode = 0) = 0;
	virtual VideoResult_t			LocatePlayableVideoFile(const char* pSearchFileName, const char* pPathID, VideoSystem_t* pPlaybackSystem, char* pPlaybackFileName, int fileNameMaxLen, VideoSystemFeature_t playMode = 0) = 0;

	// Create/destroy a video material
	virtual IVideoMaterial*			CreateVideoMaterial(const char* pMaterialName, const char* pVideoFileName, const char* pPathID = nullptr,
		VideoPlaybackFlags_t playbackFlags = 0,
		VideoSystem_t videoSystem = VideoSystem::DETERMINE_FROM_FILE_EXTENSION, bool PlayAlternateIfNotAvailable = true) = 0;

	virtual VideoResult_t			DestroyVideoMaterial(IVideoMaterial* pVideoMaterial) = 0;
	virtual int						GetUniqueMaterialID() = 0;

	// Create/destroy a video encoder		
	virtual VideoResult_t			IsRecordCodecAvailable(VideoSystem_t videoSystem, VideoEncodeCodec_t codec) = 0;

	virtual IVideoRecorder*			CreateVideoRecorder(VideoSystem_t videoSystem) = 0;
	virtual VideoResult_t			DestroyVideoRecorder(IVideoRecorder* pVideoRecorder) = 0;

	// Plays a given video file until it completes or the user presses ESC, SPACE, or ENTER
	virtual VideoResult_t			PlayVideoFileFullScreen(const char* pFileName, const char* pPathID, void* mainWindow, int windowWidth, int windowHeight, int desktopWidth, int desktopHeight, bool windowed, float forcedMinTime,
		VideoPlaybackFlags_t playbackFlags = 0,
		VideoSystem_t videoSystem = VideoSystem::DETERMINE_FROM_FILE_EXTENSION, bool PlayAlternateIfNotAvailable = true) = 0;

	// Sets the sound devices that the video will decode to
	virtual VideoResult_t			SoundDeviceCommand(VideoSoundDeviceOperation_t operation, void* pDevice = nullptr, void* pData = nullptr, VideoSystem_t videoSystem = VideoSystem::ALL_VIDEO_SYSTEMS) = 0;

	// Get the (localized) name of a codec as a string
	virtual const wchar_t*			GetCodecName(VideoEncodeCodec_t nCodec) = 0;

};
