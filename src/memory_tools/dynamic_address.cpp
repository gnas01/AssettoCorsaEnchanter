#include "dynamic_address.h"

DynamicAddress::DynamicAddress(Process* process, uintptr_t baseAddress, std::vector<unsigned int> offsets)
{
	this->process = process;
	this->baseAddress = baseAddress;
	this->offsets = offsets;
	this->dynamicMemoryAddress = FindDynamicMemoryAddress();
}

void DynamicAddress::RefreshDynamicMemoryAddress()
{
	dynamicMemoryAddress = FindDynamicMemoryAddress();
}

uintptr_t DynamicAddress::FindDynamicMemoryAddress()
{
	uintptr_t dynamicMemoryAddress = process->GetModuleBaseAddress() + baseAddress;
	for (int i = 0; i < offsets.size(); i++)
	{
		ReadProcessMemory(process->GetHandle(), (BYTE*)dynamicMemoryAddress, &dynamicMemoryAddress, sizeof(dynamicMemoryAddress), 0);
		dynamicMemoryAddress += offsets[i];
	}

	return dynamicMemoryAddress;
}
