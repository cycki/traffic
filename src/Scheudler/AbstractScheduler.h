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
    cLongHistogram packetDelayHistogram;
	double bandwidth;
    double prevTime;
    unsigned rejectedCount;
    unsigned acceptedCount;

    simtime_t processDelay;
    cMessage* processEvent;

	virtual void initialize();
	virtual void handleMessage(cMessage* );
	virtual bool receivePacket(NetPacket* , int ) = 0;
	virtual bool hasPacketsAwaitingDeparture() = 0;
	virtual NetPacket* getPacketForDeparture() = 0;
	virtual void finish();
	void initializeStatistics();
	void updateAcceptedStats(int64);
	void updateRejectedStats();
	void handleBandwidthMessage();
	void updateSendedStats(simtime_t_cref);
};

#endif /* ABSTRACTSCHEDULER_H_ */
