#pragma once
#include "../Feature/Feature.h"
#include <MinHook/MinHook.h>
#include <unordered_map>
#include <string>

class CHook
{
public:
	void* m_pOriginal = nullptr;
	void* m_pInitFunc = nullptr;
	void* m_pTarget = nullptr;

public:
	CHook(std::string sName, void* pInitFunc);

	inline void Create(void* pSrc, void* pDst)
	{
		m_pTarget = pSrc;
		MH_CreateHook(pSrc, pDst, &m_pOriginal);
	}

	template <typename T>
	inline T As() const
	{
		return reinterpret_cast<T>(m_pOriginal);
	}

	template <typename T, typename... Args>
	inline T Call(Args... args) const
	{
		return reinterpret_cast<T(__fastcall*)(Args...)>(m_pOriginal)(args...);
	}
};

#define MAKE_HOOK(name, address, type, ...) namespace Hooks \
{\
	namespace name\
	{\
		bool Init(); \
		inline CHook Hook(#name, Init); \
		using FN = type(__fastcall*)(__VA_ARGS__); \
		type __fastcall Func(__VA_ARGS__); \
	}\
} \
bool Hooks::name::Init() { if (address) {Hook.Create(reinterpret_cast<void*>(address), Func); return true;} else { SDK::Output("Amalgam", std::format("Failed to initialize hook: {}", #name).c_str()); return false;}} \
type __fastcall Hooks::name::Func(__VA_ARGS__)

class CHooks
{
private:
	bool m_bInit = true;

public:
	std::unordered_map<std::string, CHook*> m_mHooks = {};

public:
	bool Initialize(const char* sName);
	bool Unload();
};

ADD_FEATURE_CUSTOM(CHooks, Hooks, U);

#define CALL_ORIGINAL Hook.As<FN>()