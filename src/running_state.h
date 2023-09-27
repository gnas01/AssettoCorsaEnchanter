#pragma once
#include "state_machine.h"
#include "state.h"
#include "engine.h"
#include "drivetrain.h"
#include "asseto_corsa_procmon.h"

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

	float stallThreshold = 300;
	bool hasStalled = false;

	bool HasStalled();
	bool HasTurnedOn();
};

