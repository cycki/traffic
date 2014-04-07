#include "SessionAdmissionControl.h"
#include <search.h>

using namespace std;

Define_Module(SessionAdmissionControl)
/*
 Kontrolujemy przyjêcia pakietów wykorzystuj¹c do tego kontrole tworzenia nowych sesji
 Pakiet wchodzi
Sprawdzamy czy srednia pakietów przekracza zamierzon¹ wartosc
jesli nie to mozemy utworzyc nowa sesje a tym samym przyjmujemy pakiet
natomiast jesli wartosc srednia pkaietów przekracza zamierzon¹ ale nie maksymalna watrosc mozemy przyjac nowy pakiet tylko pod
warunkiem ze pochodzi on z juz istniejacej sesji.

 */

void SessionAdmissionControl::initialize() {
    //Inicjalizujêmy abstrakcyjne AC
    AbstractAdmissionControl::initialize();
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
}

bool SessionAdmissionControl::acceptMsg(NetPacket* packet) {
    double currentTime = simTime().dbl();
    if (currentTime >= previousTime + samplingPeriod) {
        blockedInCycle = false;
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
        if (blockedSessionIds.size() > 0) {
            blockedSessionIds.clear();
        }
        if (activeSessionIds.find(packet->getSessionId())
                == activeSessionIds.end()) {
            allSessions++;
        }
        lastPackets.push_back(NetPacket(*packet));
        activeSessionIds.insert(packet->getSessionId());
        accept = true;
    } else {
        if (average < maxBandwith) {
            if (!blockedInCycle) {
                blockedInCycle = true;

                std::list<double> sessionLoads;
                for (std::set<int>::iterator sessionId =
                        activeSessionIds.begin();
                        sessionId != activeSessionIds.end(); sessionId++) {
                    double cntr = 0;
                    for (std::list<NetPacket>::iterator packet =
                            lastPackets.begin(); packet != lastPackets.end();
                            packet++) {
                        if ((*packet).getSessionId() == (*sessionId)) {
                            cntr += (*packet).getByteLength();
                        }
                    }
                    sessionLoads.push_back(cntr / timeWindow);
                }
                double max = 0;
                int idx = 0;
                int maxID;
                for (std::list<double>::iterator sesLoad = sessionLoads.begin();
                        sesLoad != sessionLoads.end(); sesLoad++) {
                    if ((*sesLoad) > max) {
                        max = (*sesLoad);
                        maxID = idx;
                    }
                    idx++;
                }
                std::set<int>::iterator ses;
                for (ses = activeSessionIds.begin();
                        ses != activeSessionIds.end(); ses++) {
                    if (maxID == 0) {
                        break;
                    }
                    maxID--;
                }
                if (blockedSessionIds.find(*ses) == blockedSessionIds.end()) {
                    rejectedSessions++;
                    blockedSessionIds.insert(*ses);
                }
                activeSessionIds.erase(*ses);
            }
            bool isBlocked = false;
            for (std::set<int>::iterator blockedSes = blockedSessionIds.begin();
                    blockedSes != blockedSessionIds.end(); blockedSes++) {
                if (*blockedSes == packet->getSessionId()) {
                    isBlocked = true;
                    break;
                }
            }

            if (!isBlocked) {
                lastPackets.push_back(NetPacket(*packet));
                activeSessionIds.insert(packet->getSessionId());
                accept = true;
            }
        }
    }

    return accept;
}

void SessionAdmissionControl::finish() {
    AbstractAdmissionControl::finish();
    recordScalar("Rejected", rejectedSessions);
    recordScalar("All", allSessions);
}
