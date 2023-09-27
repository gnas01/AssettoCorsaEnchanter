#include <thread>
#include <iostream>
#include "running_state.h"
#include "waiting_state.h"
#include "state_alias.h"

RunningState::RunningState(StateMachine* stateMachine, Engine* engine, Drivetrain* drivetrain, AssetoCorsaProcMon* assetoCorsaProcMon) :
		State(stateMachine)
{
	this->assetoCorsaProcMon = assetoCorsaProcMon;

	this->drivetrain = drivetrain;
	this->engine = engine;
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
		std::this_thread::sleep_for(std::chrono::seconds(5));
		stateMachine->SetState(StateAlias::Waiting);
	}
}

bool RunningState::HasStalled()
{
	float currentRpm = engine->GetCurrentRpm();
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
	hasStalled = false;
	std::cout << "Exiting running state" << std::endl;
}
