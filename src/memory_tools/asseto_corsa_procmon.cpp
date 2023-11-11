#include "asseto_corsa_procmon.h"
#include <iostream>

AssetoCorsaProcMon::AssetoCorsaProcMon(Process* process, DynamicAddress* isPlayingAddress)
{
	this->process = process;
	this->isPlayingAddress = isPlayingAddress;
}

bool AssetoCorsaProcMon::IsRunning()
{
	if (!isRunning)
	{
		if (process->GetHandle() == 0)
		{
			return false;
		}

		isPlayingAddress->RefreshDynamicMemoryAddress();

		byte isPlayingAddressResult;
		isPlayingAddress->Read(&isPlayingAddressResult);

		if (isPlayingAddressResult == 1)
		{
			isRunning = true;
		}

		return isRunning;
	}
	else
	{
		byte isPlayingAddressResult;
		isPlayingAddress->Read(&isPlayingAddressResult);

		if (isPlayingAddressResult != 1 && isPlayingAddressResult != 0)
		{
			isRunning = process->IsValid();
		}

		return isRunning;
	}

}
