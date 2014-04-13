#include "AbstractScheduler.h"

void AbstractScheduler::initialize() {
    //statistics
    emitBandwidth = new cMessage("emitBandwith");
    delaySignal = registerSignal("delay");
    rejectedSignal = registerSignal("rejected");
    intervalSignal = registerSignal("interval");
    bandwidthSignal = registerSignal("bandwidth");
    timeRequestHistogram.setRange(0, 1700);
    timeRequestHistogram.setNumCells(1000);
    prevTime = 0;
    bandwidth = 0;
    rejectedCount = acceptedCount = 0;

    processEvent = new cMessage("processEvent");
    processDelay = par("processDelay");

    scheduleAt(simTime() + 1, emitBandwidth);
}

void AbstractScheduler::handleMessage(cMessage* msg) {
    if (msg == emitBandwidth) {
        emit(bandwidthSignal, bandwidth);
        EV << "Bandwidth1: "<< bandwidth<< endl;
        bandwidth = 0;
        scheduleAt(simTime() + 1, emitBandwidth);
    } else {
        if (msg != processEvent) {
            NetPacket* pck = check_and_cast<NetPacket*>(msg);
            bool queued = receivePacket(pck, pck->getArrivalGateId());

            if (queued) {
                emit(intervalSignal, simTime().dbl() - prevTime);
                timeRequestHistogram.collect(simTime());
                prevTime = simTime().dbl();
                emit(delaySignal, simTime() - pck->getArrivalTime());
                bandwidth += pck->getByteLength();
                EV << "Bandwidth2: "<< bandwidth<< endl;
                acceptedCount++;
                if (!processEvent->isScheduled()) {
                    scheduleAt(simTime() + processDelay, processEvent);
                }
            } else {
                emit(rejectedSignal, 1);
                rejectedCount++;
                delete pck;
            }
        } else {
            NetPacket* pck = getPacketForDeparture();
            send(pck, "out");

            if (hasPacketsAwaitingDeparture())
                scheduleAt(simTime() + processDelay, processEvent);
        }
    }
}
void AbstractScheduler::finish() {
    recordScalar("Rejected count", rejectedCount);
    recordScalar("Accepted count", acceptedCount);
    timeRequestHistogram.recordAs("TimeRequestHistogram");
}
