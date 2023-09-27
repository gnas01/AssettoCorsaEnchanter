#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "state_alias.h"

class State;

class StateMachine
{
private:
	State* currentState = nullptr;
	std::unordered_map<StateAlias, State*> states;
public:
	void SetState(StateAlias stateAlias);
	void AddState(State* state, StateAlias stateAlias);
	void Update();
};

