#pragma once
#include "process.h";
#include "dynamic_address.h"

class AssetoCorsaProcMon
{
public:
	AssetoCorsaProcMon(Process* process, DynamicAddress* idleRpmAddress);
	bool IsRunning();

private:
	Process* process;
	DynamicAddress* idleRpmAddress;
};

