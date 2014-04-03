#ifndef RR_H_
#define RR_H_

#include <list>
#include "AbstractScheduler.h"
using namespace std;

class RR: public AbstractScheduler {

private:

#ifdef _PREV_
    list<int> srcList;
#else
    list<int> priorList;
#endif

    list<list<NetPacket*>*> packetList;
    int packetSum;
    unsigned int currentQueue;
    int maxQueueSize;

public:
    virtual void initialize();
    virtual bool receivePacket(NetPacket* packet, int gateNum);
    virtual bool hasPacketsAwaitingDeparture();
    virtual NetPacket* getPacketForDeparture();

};

#endif /* RR_H_ */
