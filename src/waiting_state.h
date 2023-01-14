#pragma once
#include "state_machine.h"
#include "state.h"
#include "asseto_corsa_procmon.h"

class WaitingState: public State
{
public:
	WaitingState(StateMachine* stateMachine, Process* process, AssetoCorsaProcMon* assetoCorsaProcMon) :
		State(stateMachine, process, assetoCorsaProcMon) {};

	void Enter() override;

	void Update() override;

	void Exit() override;
};

