#pragma once
#include "memory_tools/instruction.h"

class Drivetrain {
public:
	Drivetrain(Instruction* openClutchVelocityStopper, Instruction* below5msCheck);
	void DisableAntiSlowSpeedRoll();
	void EnableAntiSlowSpeedRoll();

	void Load();
	void ClearMemory();
private:
	Instruction* openClutchVelocityStopper;
	Instruction* below5msCheck;
};