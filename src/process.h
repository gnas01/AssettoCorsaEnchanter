#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

class Process
{
public:
	Process(const wchar_t* processName);
	HANDLE GetHandle();
	uintptr_t GetModuleBaseAddress();
	DWORD GetProcessId();

	~Process();

private:
	const wchar_t* processName;
	DWORD cachedProcessId;
	HANDLE cachedHandle;
	uintptr_t cachedModuleBaseAddress;
};

