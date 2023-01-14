#pragma once
#include "state_machine.h"
#include "state.h"
#include "engine.h"
#include "drivetrain.h"

class RunningState : public State
{
public:
	RunningState(StateMachine* stateMachine, Process* process, AssetoCorsaProcMon* assetoCorsaProcMon);

	void Enter() override;

	void Update() override;

	void Exit() override;

private:
	Engine* engine;
	Drivetrain* drivetrain;
	float stallThreshold = 300;
	bool hasStalled = false;

	bool HasStalled();
	bool HasTurnedOn();
};

