#ifndef ABSTRACTGENERATOR_H_
#define ABSTRACTGENERATOR_H_

#include <omnetpp.h>
#include "NetPacket_m.h"

class AbstractGenerator : public cSimpleModule {
    protected:
    cMessage* intervalEvent;
    simsignal_t intervalSignal;
    simtime_t end;

    int priority;
    int length;
    cPar* sessionId;
    int lowerPriority;
    int upperPriority;
    int lowerSessionId;
    int upperSessionId;
    int meanLength;
    int stdDevLength;

    static int totalNumGen;
    virtual void initialize();
    virtual void handleMessage(cMessage* msg);
    virtual NetPacket* generatePacket();
    virtual simtime_t getNextPacketCreationTime(simtime_t lastPacketCreationTime) = 0;
};

#endif /* ABSTRACTGENERATOR_H_ */
