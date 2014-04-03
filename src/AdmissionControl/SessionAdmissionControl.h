#ifndef SESSIONAC_H_
#define SESSIONAC_H_

#include "AbstractAdmissionControl.h"

#include <list>
#include <set>

class SessionAdmissionControl : public AbstractAdmissionControl {
protected:
    double timeWindow;
    double samplingPeriod;
    double previousTime;
    double average;
    double targetBandwidth;
    int rejectedSessions;
    int allSessions;
    std::list<NetPacket> lastPackets;
    std::set<int> activeSessionIds;
    double terminationTimeout;
    int maxBandwith;
    virtual void initialize();
    virtual bool acceptMsg(NetPacket* packet);
    virtual void finish();
};

#endif /* SESSIONADMISSIONCONTROL_H_ */
