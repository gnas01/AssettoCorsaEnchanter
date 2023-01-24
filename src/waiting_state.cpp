#include "waiting_state.h"
#include <iostream>
#include "asseto_corsa_procmon.h"
#include "running_state.h"
#include <thread>


void WaitingState::Enter()
{
	assetoCorsa->ClearCache();
	std::cout << "Waiting for AssetoCorsa" << std::endl;
}

void WaitingState::Update()
{
	if (assetoCorsaProcMon->IsRunning())
	{
		std::cout << "Asseto Corsa is running" << std::endl;
		stateMachine->SetState(new RunningState(stateMachine, assetoCorsa, assetoCorsaProcMon));
	}
}

void WaitingState::Exit()
{
}
