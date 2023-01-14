#pragma once
#include "process.h";
#include "dynamic_address.h"

class AssetoCorsaProcMon
{
public:
	AssetoCorsaProcMon(Process* process, DynamicAddress* currentRpmAddress);
	bool IsRunning();

private:
	Process* process;
	DynamicAddress* currentRpmAddress;
};

