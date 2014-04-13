#ifndef ABSTRACTSCHEDULER_H_
#define ABSTRACTSCHEDULER_H_

#include <omnetpp.h>
#include "NetPacket_m.h"

class AbstractScheduler : public cSimpleModule{
protected:
    simsignal_t delaySignal;
    simsignal_t rejectedSignal;
    simsignal_t intervalSignal;
    simsignal_t bandwidthSignal;
    cMessage* emitBandwidth;
    cDoubleHistogram timeRequestHistogram;
	double bandwidth;
    double prevTime;
    unsigned rejectedCount;
    unsigned acceptedCount;

    simtime_t processDelay;
    cMessage* processEvent;

	virtual void initialize();
	virtual void handleMessage(cMessage* msg);
	virtual bool receivePacket(NetPacket* packet, int gateNum) = 0;
	virtual bool hasPacketsAwaitingDeparture() = 0;
	virtual NetPacket* getPacketForDeparture() = 0;
	virtual void finish();
};

#endif /* ABSTRACTSCHEDULER_H_ */
