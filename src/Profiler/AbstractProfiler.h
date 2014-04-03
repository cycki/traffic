#ifndef ABSTRACTPROFILER_H_
#define ABSTRACTPROFILER_H_

#include <omnetpp.h>
#include <list>
#include "NetPacket_m.h"

class AbstractProfiler : public cSimpleModule
{
	cMessage* bandwidthEvent;
	simsignal_t inputSignal;
	simsignal_t outputSignal;
	uint32_t inputBandwidthSum;
	uint32_t outputBandwidthSum;

	void calcMeanBandwidth();


protected:
	simtime_t endTime;
	uint32_t maxQueueSize;
	std::list<NetPacket*> queue;
	simtime_t bandwidthCalcTick;
	double inputBandwidth;
	double outputBandwidth;

	virtual void initialize();
	virtual void handleMessage(cMessage* msg);
	bool canReceive();
	virtual bool acceptPacket(NetPacket* packet, simtime_t& delay) = 0;
};

#endif /* ABSTRACTPROFILER_H_ */
