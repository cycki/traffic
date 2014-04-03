#ifndef JITTERCONTROL_H_
#define JITTERCONTROL_H_
#include "AbstractProfiler.h"

class JitterControl : public AbstractProfiler
{
	simsignal_t packetDelaySignal;

protected:
	simtime_t expectedPacketDelay;
	simtime_t currentPacketDelay;
	simtime_t lastPacketSendTime;
	simtime_t packetDelaySum;
	uint32_t packetsReceived;
	NetPacket* lastQueuedPacket;

	virtual void initialize();
	virtual bool acceptPacket(NetPacket* packet, simtime_t& delay);
};

#endif /* JITTERCONTROL_H_ */
