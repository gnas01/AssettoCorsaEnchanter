#include "waiting_state.h"
#include <iostream>
#include "../../memory_tools/asseto_corsa_procmon.h"
#include "running_state.h"
#include <thread>


void WaitingState::Enter()
{
	assetoCorsaProcess->ClearCache();
	std::cout << "Waiting for AssetoCorsa" << std::endl;
}

void WaitingState::Update()
{
	if (assetoCorsaProcMon->IsRunning())
	{
		stateMachine->SetState(StateAlias::Running);
	}
}

void WaitingState::Exit()
{
	std::cout << "Exiting waiting state" << std::endl;
}
