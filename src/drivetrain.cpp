#include "drivetrain.h"

Drivetrain::Drivetrain(Instruction* openClutchVelocityStopper, Instruction* below5msCheck)
{
	this->openClutchVelocityStopper = openClutchVelocityStopper;
	this->below5msCheck = below5msCheck;
}

void Drivetrain::DisableAntiSlowSpeedRoll()
{
    std::vector<BYTE> jmpBelow5ms{ 0xE9, 0xAB};
    below5msCheck->PatchBytes(&jmpBelow5ms);

    std::vector<BYTE> jmpOpenClutch{ 0xEB, 0x13};
	openClutchVelocityStopper->PatchBytes(&jmpOpenClutch);
}

void Drivetrain::EnableAntiSlowSpeedRoll()
{
	below5msCheck->RevertBytes();
	openClutchVelocityStopper->RevertBytes();
}

void Drivetrain::Load()
{
	below5msCheck->Load();
	openClutchVelocityStopper->Load();
}

void Drivetrain::ClearMemory()
{
	delete openClutchVelocityStopper;
	openClutchVelocityStopper = nullptr;

	delete below5msCheck;
	below5msCheck = nullptr;
}
