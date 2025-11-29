#pragma once
#include <Windows.h>

namespace CrashLog
{
	void Initialize(LPVOID lpParam);
	void Unload();
}