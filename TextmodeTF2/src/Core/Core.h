#pragma once
#include "../Utils/Feature/Feature.h"

#include <sstream>
#include <fstream>

class CCore
{
public:
	void Load();
	void Loop();
	void Unload();

	void AppendFailText(const char* sMessage, bool bCritical = false);
	void AppendSuccessText(const char* sFunction, const char* sMessage);

	bool m_bUnload = false;
	bool m_bTimeout = false;
private:
	bool m_bFilesystemLoaded = false, m_bEngineLoaded = false, m_bMatSysLoaded = false, m_bClientLoaded = false, m_bGameUILoaded = false, m_bParticlesLoaded = false, m_bMDLCacheLoaded = false, m_bVideoServicesLoaded = false, m_bVPhysicsLoaded = false;

	int LoadFilesystem();
	int LoadEngine();
	int LoadMatSys();
	int LoadClient();
	int LoadGameUI();
	int LoadParticles();
	int LoadMDLCache();
	int LoadVideoServices();
	int LoadVPhysics();

	std::stringstream ssFailStream;
};

ADD_FEATURE_CUSTOM(CCore, Core, U);
