#pragma once
#include "instruction.h"

class Drivetrain {
public:
	Drivetrain(Instruction* openClutchVelocityStopper, Instruction* below5msCheck);
	void DisableAntiSlowSpeedRoll();
	void EnableAntiSlowSpeedRoll();
private:
	Instruction* openClutchVelocityStopper;
	Instruction* below5msCheck;
};