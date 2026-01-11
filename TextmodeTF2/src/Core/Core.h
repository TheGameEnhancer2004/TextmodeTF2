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
	bool m_bFilesystemLoaded = false, m_bEngineLoaded = false, m_bMatSysLoaded = false, m_bClientLoaded = false, m_bParticlesLoaded = false;

	int LoadFilesystem();
	int LoadEngine();
	int LoadMatSys();
	int LoadClient();
	int LoadParticles();

	std::stringstream ssFailStream;
};

ADD_FEATURE_CUSTOM(CCore, Core, U);