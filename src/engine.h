#pragma once
#include "memory_tools/dynamic_address.h"
#include "memory_tools/instruction.h"

class Engine
{
public:
	Engine(DynamicAddress* idleRpm, DynamicAddress* currentRpm, Instruction* engineStall);

	void EnableEngineStall();
	void DisableEngineStall();

	float GetIdleRpm();
	float GetCurrentRpm();
	void setCurrentRpm(float value);

	void ClearMemory();

private:
	DynamicAddress* idleRpm;
	DynamicAddress* currentRpm;
	Instruction* engineStall;
};

