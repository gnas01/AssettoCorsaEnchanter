#include "asseto_corsa_procmon.h"

AssetoCorsaProcMon::AssetoCorsaProcMon(Process* process, DynamicAddress* idleRpmAddress)
{
	this->process = process;
	this->idleRpmAddress = idleRpmAddress;
}

bool AssetoCorsaProcMon::IsRunning()
{
	if (process->GetHandle() == 0)
	{
		return false;
	}

    DynamicAddress idleRpm(process, 0x01559AF0, { 0x58, 0x60, 0x38, 0x70, 0x8, 0x508 });

	int result;
	idleRpm.Read(&result);

	return result > 0;
}
