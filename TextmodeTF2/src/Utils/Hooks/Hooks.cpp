#include "Hooks.h"
#include "../../SDK/SDK.h"

#include "../Assert/Assert.h"
#include "../../Core/Core.h"
#include <format>

CHook::CHook(std::string sName, void* pInitFunc)
{
	m_pInitFunc = pInitFunc;
	U::Hooks.m_mHooks[sName] = this;
}

bool CHooks::Initialize(const char* sName)
{
	if (m_bInit)
	{
		MH_Initialize();
		m_bInit = false;
	}

	auto pHook = m_mHooks[sName];
	if (!pHook)
	{
		SDK::Output("Hooks", std::format("Failed to find hook: {}", sName).c_str());
		return false;
	}

	bool bFail{!reinterpret_cast<bool(__cdecl*)()>(pHook->m_pInitFunc)()};
	if (bFail)
	{
		SDK::Output("Hooks", std::format("Failed to initialize hook (InitFunc): {}", sName).c_str());
		return false;
	}

	bFail = MH_EnableHook(pHook->m_pTarget) != MH_OK;
	if (bFail)
		U::Core.AppendFailText(std::format("MinHook failed to enable {} hook!", sName).c_str(), true);
	else
		U::Core.AppendSuccessText("Hooks", std::format("Successfully enabled {} hook!", sName).c_str());

	return !bFail;
}

bool CHooks::Unload()
{
	return MH_Uninitialize() == MH_OK;
}