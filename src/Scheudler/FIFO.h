#ifndef FIFO_H_
#define FIFO_H_

#include <list>
#include "AbstractScheduler.h"

class FIFO : public AbstractScheduler
{
protected:
	uint32_t maxQueueSize;
	std::list<NetPacket*> awaitingPackets;

	virtual void initialize();
	virtual bool receivePacket(NetPacket* packet, int gateNum);
	virtual bool hasPacketsAwaitingDeparture();
	virtual NetPacket* getPacketForDeparture();
	bool canReceive();
};

#endif /* FIFO_H_ */
