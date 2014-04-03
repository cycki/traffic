#include "LoadShedding.h"

Define_Module(LoadShedding)

void LoadShedding::initialize()
{
	AbstractProfiler::initialize();
	criticalBandwidth = par("criticalBandwidth");
}

bool LoadShedding::acceptPacket(NetPacket* packet, simtime_t& delay)
{
	if(outputBandwidth < criticalBandwidth)
	{
		if(simTime() < endTime || endTime == 0)
			outputBandwidth += packet->getByteLength();
		return true;
	}
	else
	{
		delay = bandwidthCalcTick;
		return false;
	}
}
