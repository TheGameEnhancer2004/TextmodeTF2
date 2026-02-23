#include "BytePatches.h"

#include "../Core/Core.h"
#include <Psapi.h>

BytePatch::BytePatch(const char* sModule, const char* sSignature, int iOffset, const char* sPatch)
{
	m_sModule = sModule;
	m_sSignature = sSignature;
	m_iOffset = iOffset;

	auto vPatch = U::Memory.PatternToByte(sPatch);
	m_vPatch = vPatch;
	m_iSize = vPatch.size();
	m_vOriginal.resize(m_iSize);
}

void BytePatch::Write(std::vector<byte>& bytes)
{
	DWORD flNewProtect, flOldProtect;
	VirtualProtect(m_pAddress, m_iSize, PAGE_EXECUTE_READWRITE, &flNewProtect);
	memcpy(m_pAddress, bytes.data(), m_iSize);
	VirtualProtect(m_pAddress, m_iSize, flNewProtect, &flOldProtect);
}

bool BytePatch::Initialize()
{
	if (m_bIsPatched)
		return true;

	const auto vMatches = U::Memory.FindSignatures(m_sModule, m_sSignature, 2);
	if (vMatches.empty())
	{
		SDK::Output("BytePatches", std::format("Failed to find signature for bytepatch: {} in {}", m_sSignature, m_sModule).c_str());
		U::Core.AppendFailText(std::format("BytePatch::Initialize() failed to initialize:\n  {}\n  {}", m_sModule, m_sSignature).c_str());
		return false;
	}
	if (vMatches.size() != 1)
	{
		SDK::Output("BytePatches", std::format("Ambiguous signature for bytepatch ({} matches): {} in {}", vMatches.size(), m_sSignature, m_sModule).c_str());
		U::Core.AppendFailText(std::format("BytePatch::Initialize() ambiguous signature:\n  {}\n  {}\n  {} matches", m_sModule, m_sSignature, vMatches.size()).c_str());
		return false;
	}

	const auto hMod = GetModuleHandleA(m_sModule);
	MODULEINFO module_info;
	if (!hMod || !GetModuleInformation(GetCurrentProcess(), hMod, &module_info, sizeof(MODULEINFO)))
	{
		SDK::Output("BytePatches", std::format("Failed to query module info for {}", m_sModule).c_str());
		U::Core.AppendFailText(std::format("BytePatch::Initialize() failed module info:\n  {}", m_sModule).c_str());
		return false;
	}

	const auto uModuleBase = uintptr_t(hMod);
	const auto uModuleEnd = uModuleBase + module_info.SizeOfImage;
	const auto uAddress = uintptr_t(vMatches[0]) + m_iOffset;
	if (uAddress < uModuleBase || uAddress + m_iSize > uModuleEnd || uAddress + m_iSize < uAddress)
	{
		SDK::Output("BytePatches", std::format("Refusing out-of-module bytepatch write: {:#x} ({})", uAddress, m_sModule).c_str());
		U::Core.AppendFailText(std::format("BytePatch::Initialize() out-of-range write blocked:\n  {}\n  {}\n  {:#x}", m_sModule, m_sSignature, uAddress).c_str());
		return false;
	}

	m_pAddress = LPVOID(uAddress);

	DWORD flNewProtect, flOldProtect;
	VirtualProtect(m_pAddress, m_iSize, PAGE_EXECUTE_READWRITE, &flNewProtect);
	memcpy(m_vOriginal.data(), m_pAddress, m_iSize);
	VirtualProtect(m_pAddress, m_iSize, flNewProtect, &flOldProtect);

	Write(m_vPatch);

	SDK::Output("BytePatches", std::format("Successfully patched {:#x} ('{}', '{}')!", uintptr_t(m_pAddress), m_sModule, m_sSignature).c_str());
	return m_bIsPatched = true;
}

void BytePatch::Unload()
{
	if (!m_bIsPatched)
		return;

	Write(m_vOriginal);
	m_bIsPatched = false;
}

bool CBytePatches::Initialize(const char* cModule)
{
	bool bFail{false};
	for (auto& patch : m_mPatches[cModule])
		if (!patch.Initialize())
			bFail = true;

	if (!bFail)
		SDK::Output("BytePatches", std::format("Successfully initialized all byte patches for {}!", cModule).c_str());

	return !bFail;
}

void CBytePatches::Unload()
{
	for (auto [_, vPatches] : m_mPatches)
		for(auto& tPatch : vPatches)
			tPatch.Unload();
}
