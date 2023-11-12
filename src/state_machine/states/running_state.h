#pragma once
#include "../state_machine.h"
#include "../state.h"
#include "../../engine.h"
#include "../../drivetrain.h"
#include "../../memory_tools/asseto_corsa_procmon.h"

class RunningState : public State
{
public:
	RunningState(StateMachine* stateMachine, Engine* engine, Drivetrain* drivetrain, AssetoCorsaProcMon* assetoCorsaProcMon);

	void Enter() override;

	void Update() override;

	void Exit() override;

private:
	Engine* engine;
	Drivetrain* drivetrain;
	AssetoCorsaProcMon* assetoCorsaProcMon;

	int stallThreshold;
	bool shouldStall;
	bool shouldUseEasyStall;
	bool shouldRoll;

	bool hasStalled = false;

	const int easyStallRpm = 400;

	bool HasStalled();
	bool HasTurnedOn();
};

