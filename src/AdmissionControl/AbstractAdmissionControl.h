#ifndef ABSTRACTADMISSIONCONTROL_H_
#define ABSTRACTADMISSIONCONTROL_H_

#include <omnetpp.h>
#include "NetPacket_m.h"

class AbstractAdmissionControl: public cSimpleModule {
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
    simtime_t tick;


    virtual bool acceptMsg(NetPacket* packet) = 0;
    virtual void onCycleEnd();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* ABSTRACTADMISSIONCONTROL_H_ */
