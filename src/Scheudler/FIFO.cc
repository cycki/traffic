#include "FIFO.h"

Define_Module(FIFO);

void FIFO::initialize()
{
	AbstractScheduler::initialize();
	maxQueueSize = par("maxQueueSize");
}

bool FIFO::receivePacket(NetPacket* packet, int gateNum)
{
	if(canReceive())
	{
		awaitingPackets.push_back(packet);
		return true;
	}
	else
		return false;
}

bool FIFO::hasPacketsAwaitingDeparture()
{
	return !awaitingPackets.empty();
}

NetPacket* FIFO::getPacketForDeparture()
{
	NetPacket* pck = awaitingPackets.front();
	awaitingPackets.pop_front();

	return pck;
}

bool FIFO::canReceive()
{
	return awaitingPackets.size() < maxQueueSize || !maxQueueSize;
}
