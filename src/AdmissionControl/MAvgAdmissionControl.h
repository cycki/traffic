#ifndef MAVGADMISSIONCONTROL_H_
#define MAVGADMISSIONCONTROL_H_

#include "AbstractAdmissionControl.h"
#include <list>

class MAvgAdmissionControl : public AbstractAdmissionControl {
protected:
    double timeWindow;
    double samplingPeriod;
    double previousTime;
    double average;
    double targetAvg;
    int rejectedSessions;
    int allSessions;
    std::list<double> arrivalTimes;
    std::list<double> loadRequests;

    virtual void initialize();
    virtual bool acceptMsg(NetPacket* packet);
};

#endif /* MAVGADMISSIONCONTROL_H_ */
