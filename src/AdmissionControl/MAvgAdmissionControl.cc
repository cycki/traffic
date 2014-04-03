#include "MAvgAdmissionControl.h"

Define_Module(MAvgAdmissionControl)

void MAvgAdmissionControl::initialize()
{
    AbstractAdmissionControl::initialize();
    timeWindow = par("timeWindow");
    samplingPeriod = par("samplingPeriod");
    targetAvg = par("targetAvg");
    arrivalTimes.clear();
    loadRequests.clear();
    previousTime = 0.0;
    average = 0.0;
    WATCH(average);
    WATCH(previousTime);
}

bool MAvgAdmissionControl::acceptMsg(NetPacket* packet)
{
    double currentTime = packet->getArrivalTime().dbl();
    if (currentTime >= previousTime + samplingPeriod) {
        double minTime = currentTime - timeWindow;
        while (arrivalTimes.size() > 0 && arrivalTimes.front() < minTime) {
            arrivalTimes.pop_front();
            loadRequests.pop_front();
        }

        average = 0.0;
        for (std::list<double>::iterator load = loadRequests.begin(); load != loadRequests.end(); ++load) {
            average += *load;
        }
        average /= timeWindow;
        previousTime = currentTime;
    }
    bool ret;
    if (ret = (average + packet->getByteLength() / timeWindow < targetAvg)) {
        arrivalTimes.push_back(currentTime);
        loadRequests.push_back(packet->getByteLength());
    } else {
        EV << "pakiet przekracze wiekosc" << packet->getName() << std::endl;
    }

    return ret;
}
