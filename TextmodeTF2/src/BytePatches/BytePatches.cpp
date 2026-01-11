#include "BytePatches.h"

#include "../Core/Core.h"

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

	m_pAddress = LPVOID(U::Memory.FindSignature(m_sModule, m_sSignature));
	if (!m_pAddress)
	{
		SDK::Output("BytePatches", std::format("Failed to find signature for bytepatch: {} in {}", m_sSignature, m_sModule).c_str());
		U::Core.AppendFailText(std::format("BytePatch::Initialize() failed to initialize:\n  {}\n  {}", m_sModule, m_sSignature).c_str());
		return false;
	}

	m_pAddress = LPVOID(uintptr_t(m_pAddress) + m_iOffset);

	DWORD flNewProtect, flOldProtect;
	VirtualProtect(m_pAddress, m_iSize, PAGE_EXECUTE_READWRITE, &flNewProtect);
	memcpy(m_vOriginal.data(), m_pAddress, m_iSize);
	VirtualProtect(m_pAddress, m_iSize, flNewProtect, &flOldProtect);

	Write(m_vPatch);

	SDK::Output("BytePatches", std::format("Successfully patched {:#x} ('{}', '{}')!", uintptr_t(m_pAddress), m_sModule, m_sSignature).c_str());
	U::Core.AppendSuccessText("BytePatches", std::format("Successfully patched {:#x} ('{}', '{}')!", uintptr_t(m_pAddress), m_sModule, m_sSignature).c_str());
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
	return !bFail;
}

void CBytePatches::Unload()
{
	for (auto [_, vPatches] : m_mPatches)
		for(auto& tPatch : vPatches)
			tPatch.Unload();
}