#include "engine.h"

Engine::Engine(DynamicAddress* idleRpm, DynamicAddress* currentRpm, Instruction* engineStall)
{
    this->idleRpm = idleRpm;
    this->currentRpm = currentRpm;
    this->engineStall = engineStall;
}

void Engine::EnableEngineStall()
{
    std::vector<BYTE> jne{ 0x75, 0x28};
    engineStall->PatchBytes(&jne);
}

void Engine::DisableEngineStall()
{
    engineStall->RevertBytes();
}

int Engine::GetIdleRpm()
{
    int result = 0;

    idleRpm->Read(&result);
    return result;
}

float Engine::GetCurrentRpm()
{
    float result = 0;

    currentRpm->Read(&result);
    return result;
}

void Engine::setCurrentRpm(float value)
{
    currentRpm->Write(value);
}
