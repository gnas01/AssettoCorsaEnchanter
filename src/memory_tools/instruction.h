#pragma once
#include <Windows.h>
#include <vector>
#include "process.h"

class Instruction
{
public:
	Instruction(Process* process, uintptr_t baseAddress, unsigned int originalSize);
	void RevertBytes();
	void PatchBytes(std::vector<BYTE>* newBytes);
	void NopBytes();
private:
	unsigned int originalSize;
	std::vector<BYTE> originalBytes;
	Process* process;
	uintptr_t baseAddress;

};

