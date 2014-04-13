#ifndef TOKENBUCKET_H_
#define TOKENBUCKET_H_
#include "AbstractProfiler.h"

class TokenBucket : public AbstractProfiler
{
protected:
	int32_t tokens;
	int32_t BUCKET_CAPACITY;
	int32_t tokenIncrement;
	simtime_t lastTokenIncrement;
	NetPacket* lastDelayedPacket;

	virtual void initialize();
	virtual bool acceptPacket(NetPacket* packet, simtime_t& delay);
};

#endif /* TOKENBUCKET_H_ */
