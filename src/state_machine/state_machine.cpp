#include "state_machine.h"
#include "state.h"
#include "exceptions/duplicate_alias_exception.h"

void StateMachine::SetState(StateAlias stateAlias)
{
	if (currentState != nullptr)
	{
		currentState->Exit();
	}

	currentState = states.at(stateAlias);
	currentState->Enter();
}

void StateMachine::AddState(State* state, StateAlias stateAlias)
{
	if (states.find(stateAlias) != states.end()) {
		throw DuplicateAliasException();
	}

	states[stateAlias] = state;
}

void StateMachine::Update()
{
	currentState->Update();
}
