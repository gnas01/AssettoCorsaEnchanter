// AssetoCorsaEnchanter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "process.h"
#include "asseto_corsa_procmon.h"
#include "state_machine.h"
#include "waiting_state.h"
#include <thread>

int main()
{
    StateMachine* stateMachine = new StateMachine();

    Process* assetoCorsa = new Process(L"acs.exe");

    DynamicAddress* currentRpm = new DynamicAddress(assetoCorsa, 0x01559AF0, { 0x38, 0xC0, 0x10, 0xF8, 0x48, 0x20, 0x5D8 });
    DynamicAddress* idleRpm = new DynamicAddress(assetoCorsa, 0x01559AF0, { 0x58, 0x60, 0x38, 0x70, 0x8, 0x508 });
    AssetoCorsaProcMon* assetoCorsaProcMon = new AssetoCorsaProcMon(assetoCorsa, currentRpm, idleRpm);

    stateMachine->SetState(new WaitingState(stateMachine, assetoCorsa, assetoCorsaProcMon));

     while (1) 
     {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stateMachine->Update();
     }

     delete stateMachine;
     stateMachine = nullptr;

     delete assetoCorsa;
     assetoCorsa = nullptr;

     delete currentRpm;
     currentRpm = nullptr;

     delete idleRpm;
     idleRpm = nullptr;

     delete assetoCorsaProcMon;
     assetoCorsa = nullptr;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
