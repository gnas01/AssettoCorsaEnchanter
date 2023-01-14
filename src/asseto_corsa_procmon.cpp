#include "asseto_corsa_procmon.h"

AssetoCorsaProcMon::AssetoCorsaProcMon(Process* process, DynamicAddress* currentRpmAddress)
{
	this->process = process;
	this->currentRpmAddress = currentRpmAddress;
}

bool AssetoCorsaProcMon::IsRunning()
{
	if (process->GetHandle() == 0)
	{
		return false;
	}

	currentRpmAddress->RefreshDynamicMemoryAddress();

	int result;
	currentRpmAddress->Read(&result);

	return result > 0;
}
