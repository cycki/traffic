#ifndef LOADSHEDDING_H_
#define LOADSHEDDING_H_
#include "AbstractProfiler.h"

class LoadShedding : public AbstractProfiler
{
protected:

	double criticalBandwidth;
	virtual void initialize();
	virtual bool acceptPacket(NetPacket* packet, simtime_t& delay);
};

#endif /* LOADSHEDDING_H_ */
