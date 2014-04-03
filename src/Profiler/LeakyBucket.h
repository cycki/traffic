#ifndef LEAKYBUCKET_H_
#define LEAKYBUCKET_H_

#include "AbstractProfiler.h"

class LeakyBucket: public AbstractProfiler {
	int32_t MAKSYMALNE_CIEKNIECIE;
	int32_t ileMozeWyciec;
	simtime_t lastFlowIncrement;
	NetPacket* lastDelayedPacket;

	virtual void initialize();
	virtual bool acceptPacket(NetPacket* packet, simtime_t& delay);

};

#endif /* LEAKYBUCKET_H_ */
