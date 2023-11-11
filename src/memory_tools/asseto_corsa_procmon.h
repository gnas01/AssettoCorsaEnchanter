#pragma once
#include "process.h";
#include "dynamic_address.h"

class AssetoCorsaProcMon
{
public:
	AssetoCorsaProcMon(Process* process, DynamicAddress* isPlayingAddress);
	bool IsRunning();

private:
	Process* process;
	DynamicAddress* isPlayingAddress;
	bool isRunning = false;
};

