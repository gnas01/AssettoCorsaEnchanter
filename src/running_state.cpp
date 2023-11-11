#include <thread>
#include <iostream>
#include "running_state.h"
#include "waiting_state.h"
#include "state_alias.h"
#include "configuration.h"

RunningState::RunningState(StateMachine* stateMachine, Engine* engine, Drivetrain* drivetrain, AssetoCorsaProcMon* assetoCorsaProcMon) :
	State(stateMachine)
{
	this->assetoCorsaProcMon = assetoCorsaProcMon;

	this->drivetrain = drivetrain;
	this->engine = engine;

	Configuration* configuration = Configuration::GetInstance();
	shouldRoll = configuration->GetShouldRoll();
	shouldStall = configuration->GetShouldStall();
	stallThreshold = configuration->GetStallThreshold();
}

void RunningState::Enter()
{
	if (shouldRoll)
		drivetrain->DisableAntiSlowSpeedRoll();
}

void RunningState::Update()
{
	if (HasTurnedOn() && shouldStall)
	{
		std::cout << "Disabling engine stall" << std::endl;
		engine->DisableEngineStall();
		hasStalled = false;
	}
	else if (HasStalled() && shouldStall)
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
