#include "../SDK/SDK.h"
#include "../SDK/Definitions/Interfaces/IVideoServices.h"

// IVideoMaterial* CreateVideoMaterial(const char* pMaterialName, const char* pVideoFileName, const char* pPathID = nullptr, VideoPlaybackFlags_t playbackFlags = 0, VideoSystem_t videoSystem = VideoSystem::DETERMINE_FROM_FILE_EXTENSION, bool PlayAlternateIfNotAvailable = true)
MAKE_HOOK(IVideoServices_CreateVideoMaterial, U::Memory.GetVFunc(I::VideoServices, 18), IVideoMaterial*, // 18
	void* rcx, const char* pMaterialName, const char* pVideoFileName, const char* pPathID, VideoPlaybackFlags_t playbackFlags, VideoSystem_t videoSystem, bool PlayAlternateIfNotAvailable)
{
	return nullptr;
}

// VideoResult_t PlayVideoFileFullScreen(const char* pFileName, const char* pPathID, void* mainWindow, int windowWidth, int windowHeight, int desktopWidth, int desktopHeight, bool windowed, float forcedMinTime, VideoPlaybackFlags_t playbackFlags = 0, VideoSystem_t videoSystem = VideoSystem::DETERMINE_FROM_FILE_EXTENSION, bool PlayAlternateIfNotAvailable = true)
MAKE_HOOK(IVideoServices_PlayVideoFileFullScreen, U::Memory.GetVFunc(I::VideoServices, 24), VideoResult_t, // 24
	void* rcx, const char* pFileName, const char* pPathID, void* mainWindow, int windowWidth, int windowHeight, int desktopWidth, int desktopHeight, bool windowed, float forcedMinTime, VideoPlaybackFlags_t playbackFlags, VideoSystem_t videoSystem, bool PlayAlternateIfNotAvailable)
{
	return VideoResult::SUCCESS;
}
