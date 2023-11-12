#include "instruction.h"

Instruction::Instruction(Process* process, uintptr_t baseAddress, unsigned int originalSize)
{
	this->process = process;
	this->baseAddress = baseAddress;
    this->originalSize = originalSize;
}

void Instruction::Load()
{
    originalBytes.resize(originalSize);
    ReadProcessMemory(process->GetHandle(), (LPCVOID)(baseAddress + process->GetModuleBaseAddress()), &originalBytes[0], originalSize, NULL);
}

void Instruction::RevertBytes()
{
	DWORD oldMemoryPermissions;
    BYTE* destinationAddress = (BYTE*)process->GetModuleBaseAddress() + baseAddress;
    VirtualProtectEx(process->GetHandle(), destinationAddress, originalSize, PAGE_EXECUTE_READWRITE, &oldMemoryPermissions);
    WriteProcessMemory(process->GetHandle(), destinationAddress, &originalBytes[0], originalSize, NULL);
    VirtualProtectEx(process->GetHandle(), destinationAddress, originalSize, oldMemoryPermissions, &oldMemoryPermissions);
}

void Instruction::PatchBytes(std::vector<BYTE>* newBytes)
{
    DWORD oldMemoryPermissions;
    BYTE* destinationAddress = (BYTE*)process->GetModuleBaseAddress() + baseAddress;
    VirtualProtectEx(process->GetHandle(), destinationAddress, originalSize, PAGE_EXECUTE_READWRITE, &oldMemoryPermissions);

    if (newBytes->size() < originalSize) 
    {
        newBytes->resize(originalSize);
        std::fill(newBytes->begin() + newBytes->size(), newBytes->end(), 0x90);
    }

    WriteProcessMemory(process->GetHandle(), destinationAddress, &(*newBytes)[0], originalSize, NULL);
    VirtualProtectEx(process->GetHandle(), destinationAddress, originalSize, oldMemoryPermissions, &oldMemoryPermissions); 
}

void Instruction::NopBytes()
{
    std::vector<BYTE> nopArray(originalSize, 0x90);
    PatchBytes(&nopArray);
}

