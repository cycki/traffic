#include "LIFO.h"

Define_Module(LIFO)

void LIFO::initialize()
{
	AbstractScheduler::initialize();
	maxQueueSize = par("maxQueueSize");
}

bool LIFO::receivePacket(NetPacket* packet, int gateNum)
{
	if(canReceive())
	{
		awaitingPackets.push_back(packet);
		return true;
	}
	else
		return false;
}

bool LIFO::hasPacketsAwaitingDeparture()
{
	return !awaitingPackets.empty();
}

NetPacket* LIFO::getPacketForDeparture()
{
	NetPacket* pck = awaitingPackets.back();
	awaitingPackets.pop_back();

	return pck;
}

bool LIFO::canReceive()
{
	return awaitingPackets.size() < maxQueueSize || !maxQueueSize;
}
