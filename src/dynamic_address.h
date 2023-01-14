#pragma once
#include "process.h"
#include <vector>

class DynamicAddress
{
public:
	DynamicAddress(Process* process, uintptr_t baseAddress, std::vector<unsigned int> offsets);
	
	template <typename T>
	void Write(T value)
	{
		WriteProcessMemory(process->GetHandle(), (BYTE*)dynamicMemoryAddress, &value, sizeof(value), nullptr);
	}

	template <typename T>
	void Read(T* result)
	{
		ReadProcessMemory(process->GetHandle(), (BYTE*)dynamicMemoryAddress, result, sizeof(*result), nullptr);
	}

	void RefreshDynamicMemoryAddress();
private:
	uintptr_t FindDynamicMemoryAddress();

	std::vector<unsigned int> offsets;
	uintptr_t baseAddress;
	Process* process;
	uintptr_t dynamicMemoryAddress;
};


