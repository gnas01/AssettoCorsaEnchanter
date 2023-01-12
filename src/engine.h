#pragma once
#include "dynamic_address.h"
#include "instruction.h"

class Engine
{
public:
	Engine(DynamicAddress* idleRpm, DynamicAddress* currentRpm, Instruction* engineStall);

	void EnableEngineStall();
	void DisableEngineStall();

	int GetIdleRpm();
	float GetCurrentRpm();
	void setCurrentRpm(float value);

private:
	DynamicAddress* idleRpm;
	DynamicAddress* currentRpm;
	Instruction* engineStall;
};

