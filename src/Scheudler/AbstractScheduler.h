#ifndef ABSTRACTSCHEDULER_H_
#define ABSTRACTSCHEDULER_H_

#include <omnetpp.h>
#include "NetPacket_m.h"

class AbstractScheduler : public cSimpleModule
{
	cMessage* processEvent;

protected:

	virtual void initialize();
	virtual void handleMessage(cMessage* msg);
	virtual bool receivePacket(NetPacket* packet, int gateNum) = 0;
	virtual bool hasPacketsAwaitingDeparture() = 0;
	virtual NetPacket* getPacketForDeparture() = 0;
};

#endif /* ABSTRACTSCHEDULER_H_ */
