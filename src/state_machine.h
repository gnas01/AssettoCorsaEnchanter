#pragma once
class State;

class StateMachine
{
private:
	State* currentState = nullptr;
public:
	void SetState(State* state);
	void Update();
};

