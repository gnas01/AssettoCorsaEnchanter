#pragma once
#include "state_machine.h"
#include "state.h"
#include "../memory_tools/asseto_corsa_procmon.h"

class WaitingState: public State
{
public:
	WaitingState(StateMachine* stateMachine, Process* assetoCorsaProcess, AssetoCorsaProcMon* assetoCorsaProcMon) :
		State(stateMachine) {
		this->assetoCorsaProcMon = assetoCorsaProcMon;
		this->assetoCorsaProcess = assetoCorsaProcess;
	};

	void Enter() override;

	void Update() override;

	void Exit() override;

private:
	Process* assetoCorsaProcess;
	AssetoCorsaProcMon* assetoCorsaProcMon;
};


