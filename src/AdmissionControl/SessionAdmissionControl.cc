#include "SessionAdmissionControl.h"
#include <search.h>

using namespace std;

Define_Module(SessionAdmissionControl)

void SessionAdmissionControl::initialize() {
    timeWindow = par("timeWindow");
    samplingPeriod = par("samplingPeriod");
    terminationTimeout = par("terminationTimeout");
    maxBandwith = par("maxBandwith");
    targetBandwidth = par("targetBandwidth");
    lastPackets.clear();
    activeSessionIds.clear();
    rejectedSessions = 0;
    allSessions = 0;
    average = 0;
    prevTime = 0;
    ev << "max bandwidth\t\t" << maxBandwith << std::endl;
    ev << "target avg\t\t" << targetBandwidth << std::endl;
    AbstractAdmissionControl::initialize();
}

bool SessionAdmissionControl::acceptMsg(NetPacket* packet) {
    double currentTime = simTime().dbl();
    if (currentTime >= previousTime + samplingPeriod) {
        double minTime = currentTime - timeWindow;

        while (lastPackets.size() > 0
                && lastPackets.front().getArrivalTime() < minTime) {
            lastPackets.pop_front();
        }

        average = 0.0;
        for (std::list<NetPacket>::iterator packet = lastPackets.begin();
                packet != lastPackets.end(); ++packet) {
            average += (*packet).getByteLength();
        }

        average /= timeWindow;

        previousTime = currentTime;

        activeSessionIds.clear();
        if (lastPackets.size() > 0) {
            for (std::list<NetPacket>::iterator packet = lastPackets.begin();
                    packet != lastPackets.end(); ++packet) {
                activeSessionIds.insert((*packet).getSessionId());
            }
        }
    }

    bool accept = false;

    if (average < targetBandwidth) {

        lastPackets.push_back(NetPacket(*packet));
        if (activeSessionIds.find(packet->getSessionId())
                == activeSessionIds.end()) {
            allSessions++;
        }
        activeSessionIds.insert(packet->getSessionId());
        accept = true;
    } else {
        if (average < maxBandwith) {
            if (activeSessionIds.find(packet->getSessionId())
                    != activeSessionIds.end()) {
                lastPackets.push_back(NetPacket(*packet));
                accept = true;
            } else {
                rejectedSessions++;
            }
        }
    }

    return accept;
}

void SessionAdmissionControl::finish() {
    AbstractAdmissionControl::finish();
    recordScalar("Rejected sessions count", rejectedSessions);
    recordScalar("All sessions count", allSessions);
}
