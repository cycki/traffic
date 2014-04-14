#ifndef REDADMISSIONCOTROL_H_
#define REDADMISSIONCOTROL_H_

#include <AbstractAdmissionControl.h>
#include <list>

class REDAdmissionControl : public AbstractAdmissionControl {
protected:
    void initialize();
    bool acceptMsg(NetPacket* packet);
    void handleMessage(cMessage* msg);
    double thresholdMin;
    double thresholdMax;

private:
    double currentAvgQueueLength;
    int currentQueueLengthCount;
    double packetDropingProbability;
    cMessage* timeForNextPacketSending;
    cMessage* intervalEvent;
    std::list<NetPacket*> packetQueue;
    void calculateAvgQueueLength();
    double calculatePacketDropingProbability();
};

#endif /* REDADMISSIONCOTROL_H_ */
