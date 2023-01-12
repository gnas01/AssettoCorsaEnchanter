#include "drivetrain.h"

Drivetrain::Drivetrain(Instruction* openClutchVelocityStopper, Instruction* below5msCheck)
{
	this->openClutchVelocityStopper = openClutchVelocityStopper;
	this->below5msCheck = below5msCheck;
}

void Drivetrain::DisableAntiSlowSpeedRoll()
{
    std::vector<BYTE> jmp{ 0xE9, 0xAB};
    below5msCheck->PatchBytes(&jmp);
}

void Drivetrain::EnableAntiSlowSpeedRoll()
{
	below5msCheck->RevertBytes();
}
