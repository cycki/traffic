#ifndef WRR_H_
#define WRR_H_

#include <AbstractScheduler.h>

class WRR : public AbstractScheduler
{
protected:
	int32_t maxQueueSize;
	int32_t queuesNum;
	int32_t currentQueue;
	cPacketQueue** queues;
	double* weights;
	double* credits;

	virtual void initialize();
	~WRR();
	virtual bool receivePacket(NetPacket* packet, int gateNum);
	virtual bool hasPacketsAwaitingDeparture();
	virtual NetPacket* getPacketForDeparture();
	bool canReceive(int32_t queueNum);
	void nextQueue();
};

#endif /* WRR_H_ */
