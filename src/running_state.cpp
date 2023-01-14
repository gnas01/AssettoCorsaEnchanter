#include "running_state.h"
#include "waiting_state.h"
#include <thread>


#include <iostream>

RunningState::RunningState(StateMachine* stateMachine, Process* process, AssetoCorsaProcMon* assetoCorsaProcMon) :
		State(stateMachine, process, assetoCorsaProcMon)
{
    Instruction* below5msCheck = new Instruction(assetoCorsa, 0x2762F0, 3);
    Instruction* openClutchVelocityStopper = new Instruction(assetoCorsa, 0x269E3F, 3);
	drivetrain = new Drivetrain(openClutchVelocityStopper, below5msCheck);

    DynamicAddress* idleRpm = new DynamicAddress(assetoCorsa, 0x01559AF0, { 0x58, 0x60, 0x38, 0x70, 0x8, 0x508 });
    DynamicAddress* currentRpm = new DynamicAddress(assetoCorsa, 0x01559AF0, { 0x38, 0xC0, 0x10, 0xF8, 0x48, 0x20, 0x5D8 });
    Instruction* engineStall = new Instruction(assetoCorsa, 0x288519, 2);
	engine = new Engine(idleRpm, currentRpm, engineStall);
}

void RunningState::Enter()
{
	drivetrain->DisableAntiSlowSpeedRoll();
}

void RunningState::Update()
{
	if (HasTurnedOn())
	{
		std::cout << "Disabling engine stall" << std::endl;
		engine->DisableEngineStall();
		hasStalled = false;
	}
	else if (HasStalled())
	{
		std::cout << "Stalling car" << std::endl;
		engine->EnableEngineStall();
		engine->setCurrentRpm(0);
		hasStalled = true;
	}

	if (!assetoCorsaProcMon->IsRunning())
	{
		stateMachine->SetState(new WaitingState(stateMachine, assetoCorsa, assetoCorsaProcMon));
	}
}

bool RunningState::HasStalled()
{
	float currentRpm = engine->GetCurrentRpm();
	std::cout << currentRpm << std::endl;
	int idleRpm = engine->GetIdleRpm();

	return (currentRpm + stallThreshold < idleRpm) && !hasStalled;
}

bool RunningState::HasTurnedOn()
{
	float currentRpm = engine->GetCurrentRpm();
	float idleRpm = engine->GetIdleRpm();
	return (currentRpm >= idleRpm - stallThreshold) && hasStalled;
}

void RunningState::Exit()
{
}
