// AssetoCorsaEnchanter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "process.h"
#include "memory_tools/asseto_corsa_procmon.h"
#include "state_machine/state_machine.h"
#include "state_machine/states/waiting_state.h"
#include "state_machine/states/running_state.h"
#include "state_machine/state_alias.h"
#include "engine.h"
#include "drivetrain.h"
#include <thread>
#include "config/configuration.h"


Engine* BuildEngine(Process* assetoCorsa);
Drivetrain* BuildDrivetrain(Process* assetoCorsa);

int main()
{
    Configuration::GetInstance()->ParseFile("config.txt");

    StateMachine* stateMachine = new StateMachine();

    Process* assetoCorsaProcess = new Process(L"acs.exe");

    Engine* engine = BuildEngine(assetoCorsaProcess);
    Drivetrain* drivetrain = BuildDrivetrain(assetoCorsaProcess);

    DynamicAddress* isPlayingAddress = new DynamicAddress(assetoCorsaProcess, 0x01559AF0, { 0x38, 0x118, 0x1f8, 0x198, 0x68, 0x150 });

    AssetoCorsaProcMon* assetoCorsaProcMon = new AssetoCorsaProcMon(assetoCorsaProcess, isPlayingAddress);


    WaitingState* waitingState = new WaitingState(stateMachine, assetoCorsaProcess, assetoCorsaProcMon);
    RunningState* runningState = new RunningState(stateMachine, engine, drivetrain, assetoCorsaProcMon);

    stateMachine->AddState(waitingState, StateAlias::Waiting);
    stateMachine->AddState(runningState, StateAlias::Running);

    stateMachine->SetState(StateAlias::Waiting);

    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stateMachine->Update();
    }

    engine->ClearMemory();
    drivetrain->ClearMemory();

    delete waitingState;
    waitingState = nullptr;
    delete runningState;
    runningState = nullptr;

    delete stateMachine;
    stateMachine = nullptr;

    delete assetoCorsaProcess;
    assetoCorsaProcess = nullptr;

    delete isPlayingAddress;
    isPlayingAddress = nullptr;

    delete assetoCorsaProcMon;
    assetoCorsaProcMon = nullptr;
}

Engine* BuildEngine(Process* assetoCorsaProcess)
{
    DynamicAddress* idleRpm = new DynamicAddress(assetoCorsaProcess, 0x01559AF0, { 0x58, 0x60, 0x38, 0x70, 0x8, 0x508 });
    DynamicAddress* currentRpm = new DynamicAddress(assetoCorsaProcess, 0x01559AF0, { 0x38, 0xC0, 0x10, 0xF8, 0x48, 0x20, 0x5D8 });
    Instruction* engineStall = new Instruction(assetoCorsaProcess, 0x288519, 2);
    return new Engine(idleRpm, currentRpm, engineStall);
}

Drivetrain* BuildDrivetrain(Process* assetoCorsa)
{
    Instruction* below5msCheck = new Instruction(assetoCorsa, 0x2762F0, 3);
    Instruction* openClutchVelocityStopper = new Instruction(assetoCorsa, 0x269E3F, 3);
    return new Drivetrain(openClutchVelocityStopper, below5msCheck);
}
