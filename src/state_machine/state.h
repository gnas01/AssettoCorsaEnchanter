#pragma once

class StateMachine;
class Process;
class AssetoCorsaProcMon;

class State
{
public:
	State(StateMachine* stateMachine)
	{
		this->stateMachine = stateMachine;
	} 

	virtual void Enter() = 0;

	virtual void Update() = 0;

	virtual void Exit() = 0;

protected:
	StateMachine* stateMachine;
};

