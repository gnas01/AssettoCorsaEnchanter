#include "state_machine.h"
#include "state.h"
#include "process.h"
#include "asseto_corsa_procmon.h"

void StateMachine::SetState(State* state)
{
	if (currentState != nullptr)
	{
		currentState->Exit();
	}

	currentState = state;
	currentState->Enter();
}

void StateMachine::Update()
{
	currentState->Update();
}
