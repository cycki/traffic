#ifndef LIFO_H_
#define LIFO_H_

#include <list>
#include "AbstractScheduler.h"

class LIFO : public AbstractScheduler
{

	uint32_t maxQueueSize;
	std::list<NetPacket*> awaitingPackets;

	virtual void initialize();
	virtual bool receivePacket(NetPacket* packet, int gateNum);
	virtual bool hasPacketsAwaitingDeparture();
	virtual NetPacket* getPacketForDeparture();

	bool canReceive();
};

#endif /* LIFO_H_ */
