#include "process.h"

Process::Process(const wchar_t* processName)
{
	this->processName = processName;
	this->cachedProcessId = 0;
	this->cachedModuleBaseAddress = 0;
	this->cachedHandle = 0;
}

bool Process::IsValid()
{
    return cachedHandle != 0;
}

HANDLE Process::GetHandle()
{
	if (cachedHandle != 0)
	{
		return cachedHandle;
	}

	DWORD processId = GetProcessId();

	return OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);
}

DWORD Process::GetProcessId()
{
	if (cachedProcessId != 0)
		return cachedProcessId;

	DWORD processId = 0;

	// Take a snapshot of all processes in the system
	HANDLE snapshot = (CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (snapshot == INVALID_HANDLE_VALUE)
	{
		return processId;
	}

	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(processEntry);

    // Iterate through all processes
    bool isFound = Process32First(snapshot, &processEntry);
    while (isFound)
    {
        // Check if the current process matches the given name
        if (!_wcsicmp(processEntry.szExeFile, processName))
        {
            processId = processEntry.th32ProcessID;
            break;
        }

        isFound = Process32Next(snapshot, &processEntry);
    }

	CloseHandle(snapshot);
	return processId;
}

uintptr_t Process::GetModuleBaseAddress()
{
	if (cachedModuleBaseAddress != 0)
	{
		return cachedModuleBaseAddress;
	}

	DWORD processId = GetProcessId();

    uintptr_t moduleBaseAddress = 0;

    // Take a snapshot of all modules in the specified process
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

    if (snapshot == INVALID_HANDLE_VALUE)
    {
        return moduleBaseAddress;
    }

    MODULEENTRY32 moduleEntry = { sizeof(moduleEntry) };

    // Iterate through all modules
    BOOL isFound = Module32First(snapshot, &moduleEntry);
    while (isFound)
    {
        // Check if the current module matches the given name
        if (!_wcsicmp(moduleEntry.szModule, processName))
        {
            moduleBaseAddress = (uintptr_t)moduleEntry.modBaseAddr;
            break;
        }

        isFound = Module32Next(snapshot, &moduleEntry);
    }

    // Clean up the snapshot handle
    CloseHandle(snapshot);
    return moduleBaseAddress;
}

Process::~Process()
{
    CloseHandle(cachedHandle);
}
