#include "SDK.h"

void SDK::Output(const char* cFunction, const char* cLog, bool bLogFile, int iMessageBox)
{
#ifdef _DEBUG
	if (!GetConsoleWindow())
	{
		AllocConsole();
		FILE* pFile;
		freopen_s(&pFile, "CONOUT$", "w", stdout);
	}
#endif

	if (cLog)
	{
		std::string sLog = std::format("[{}] {}", cFunction, cLog);
#ifdef _DEBUG
		printf("%s\n", sLog.c_str());
		fflush(stdout);
#endif

		if (bLogFile)
			OutputFile(TEXTMODE_LOG_FILE, (sLog + "\n").c_str());
		if (iMessageBox != -1)
			MessageBox(nullptr, cLog, cFunction, iMessageBox);
	}
	else
	{
#ifdef _DEBUG
		printf("%s\n", cFunction);
		fflush(stdout);
#endif

		if (bLogFile)
			OutputFile(TEXTMODE_LOG_FILE, std::format("{}\n", cFunction).c_str());
		if (iMessageBox != -1)
			MessageBox(nullptr, "", cFunction, iMessageBox);
	}
}

void SDK::OutputFile(const char* cOutputFileName, const char* cMsg)
{
	std::string sPath = G::AppdataPath.empty() ? G::CurrentPath + "\\" : G::AppdataPath;
	if (sPath == "\\" || sPath.empty())
	{
		char szPath[MAX_PATH];
		if (GetModuleFileNameA(NULL, szPath, MAX_PATH))
		{
			std::string sModulePath(szPath);
			sPath = sModulePath.substr(0, sModulePath.find_last_of("\\/")) + "\\";
		}
	}

	try
	{
		std::ofstream file;
		file.open(sPath + cOutputFileName, std::ios::app);
		if (file.is_open())
		{
			file << cMsg;
			file.flush();
			file.close();
		}
		
		if (!file.is_open()) {
			std::ofstream backupFile;
			backupFile.open("C:\\TextmodeLog_Backup.log", std::ios::app);
			if (backupFile.is_open()) {
				backupFile << cMsg;
				backupFile.close();
			}
		}
	}
	catch (...) {}
}

bool SDK::BlacklistFile(const char* cFileName)
{
	const static char* blacklist[] = {
		".ani", ".wav", ".mp3", ".vvd", ".vtx", ".vtf", ".vfe", ".cache",
		".jpg", ".png", ".tga", ".dds",  // Texture files we dont need in textmode
		".phy",  // Physics
		".dem",  // Demo and log files
		".vcd",  // Scene files
		".ain",  // AI node graph
		".lst",  // Manifests
		".pcf"   // Particle systems
	};

	if (!cFileName || !std::strncmp(cFileName, "materials/console/", 18))
		return false;

	std::size_t len = std::strlen(cFileName);
	if (len <= 3)
		return false;

	auto ext_p = strrchr(cFileName, '.');
	if (!ext_p)
		return false;

	// NEVER block .bsp files - they are essential for map loading
	if (!std::strcmp(ext_p, ".bsp"))
		return false;

	// NEVER block .nav files - navengine needs it obviosuly lol
	if (!std::strcmp(ext_p, ".nav"))
		return false;

	// Block all particle effects during map load
	if (!std::strcmp(ext_p, ".pcf"))
		return true;

	// Block all soundscapes during map load
	if (std::strstr(cFileName, "soundscape") && std::strcmp(ext_p, ".txt"))
		return true;

	// Block detail sprites and props
	if (std::strstr(cFileName, "detail") || std::strstr(cFileName, "props_"))
		return true;

	// Block skybox materials during map load
	if (std::strstr(cFileName, "skybox"))
		return true;

	// Block all ambient sounds
	if (std::strstr(cFileName, "ambient"))
		return true;

	// Block models that aren't players or essential gameplay items
	if (!std::strcmp(ext_p, ".mdl"))
	{
		if (std::strstr(cFileName, "player/") || std::strstr(cFileName, "buildables/") || std::strstr(cFileName, "weapons/") || std::strstr(cFileName, "empty.mdl") || std::strstr(cFileName, "error.mdl"))
			return false;

		return true;
	}

	if (!std::strcmp(ext_p, ".vmt"))
	{
		// Only allow essential UI materials
		if (!std::strstr(cFileName, "hud") && !std::strstr(cFileName, "vgui") && !std::strstr(cFileName, "console"))
			return true;

		/* Not loading it causes extreme console spam */
		if (std::strstr(cFileName, "corner"))
			return false;
		/* minor console spam */
		if (std::strstr(cFileName, "hud") || std::strstr(cFileName, "vgui"))
			return false;

		return true;
	}

	if (std::strstr(cFileName, "sound.cache") || std::strstr(cFileName, "tf2_sound") || std::strstr(cFileName, "game_sounds"))
		return false;
	if (!std::strncmp(cFileName, "sound/player/footsteps", 22))
		return false;
	if (!std::strncmp(cFileName, "/decal", 6))
		return true;

	for (int i = 0; i < sizeof(blacklist) / sizeof(blacklist[0]); ++i)
		if (!std::strcmp(ext_p, blacklist[i]))
			return true;

	return false;
}

double SDK::PlatFloatTime()
{
	static auto Plat_FloatTime = U::Memory.GetModuleExport<double(*)()>("tier0.dll", "Plat_FloatTime");
	return Plat_FloatTime();
}