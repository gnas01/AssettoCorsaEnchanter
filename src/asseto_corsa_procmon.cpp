#include "asseto_corsa_procmon.h"
#include <iostream>

AssetoCorsaProcMon::AssetoCorsaProcMon(Process* process, DynamicAddress* currentRpmAddress, DynamicAddress* idleRpmAddress)
{
	this->process = process;
	this->currentRpmAddress = currentRpmAddress;
	this->idleRpmAddress = idleRpmAddress;
}

/**
* Previous implementation was only checking for
* idleRpmAddress, but it turns out that by the time
* idleRpmAddress is initialized in memory, currentRpmAddress is not.
* We cannot only check for the currentRpmAddress if it is >=0 since, when
* the engine stalls currentRpmAddress becomes 0. As a result isRunning falsely 
* returns false. 
* 
* As a workaround a check whether the currentRpm and idleRpm is above 0
* and the currentRpm and idleRpm is equal is made to ensure that the game is running
* Drawbacks are that when the game starts, it takes a few seconds for the current rpms to
* rise to the idleRpm.
* 
* TODO: Find a different address that we can check if everything is loaded and initialized.
*/
bool AssetoCorsaProcMon::IsRunning()
{
	if (!isRunning)
	{
		if (process->GetHandle() == 0)
		{
			return false;
		}

		currentRpmAddress->RefreshDynamicMemoryAddress();
		idleRpmAddress->RefreshDynamicMemoryAddress();

		float currentRpmResult;
		currentRpmAddress->Read(&currentRpmResult);

		int idleRpmResult;
		idleRpmAddress->Read(&idleRpmResult);

		int idleCurrentDiff = idleRpmResult - static_cast<int>(currentRpmResult);

		if (currentRpmResult > 0 && idleRpmResult > 0 && idleCurrentDiff == 0)
		{
			isRunning = true;
		}

		return isRunning;
	}
	else
	{
		int result;
		idleRpmAddress->Read(&result);

		if (result <= 0)
		{
			isRunning = process->IsValid();
		}

		return isRunning;
	}

}
