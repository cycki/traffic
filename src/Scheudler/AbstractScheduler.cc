#include "AbstractScheduler.h"

void AbstractScheduler::initialize() {
    processEvent = new cMessage("processEvent");
    processDelay = par("processDelay");

    initializeStatistics();
}

void AbstractScheduler::initializeStatistics() {
    prevTime = 0;
    bandwidth = 0;
    rejectedCount = acceptedCount = 0;
    delaySignal = registerSignal("delay");
    rejectedSignal = registerSignal("rejected");
    intervalSignal = registerSignal("interval");
    bandwidthSignal = registerSignal("bandwidth");
    timeRequestHistogram.setRange(0, 1700);
    timeRequestHistogram.setNumCells(1000);
    emitBandwidth = new cMessage("emitBandwith");
    scheduleAt(simTime() + 1, emitBandwidth);
}
void AbstractScheduler::handleMessage(cMessage* msg) {
    if (msg == emitBandwidth) {
        handleBandwidthMessage();
    } else {
        if (msg != processEvent) {
            NetPacket* pck = check_and_cast<NetPacket*>(msg);
            bool queued = receivePacket(pck, pck->getArrivalGateId());

            if (queued) {
                updateAcceptedStats(pck->getByteLength());
                pck->setTimestamp();
                if (!processEvent->isScheduled()) {
                    EV << "Wejcie: "<< pck->getName() << " Timestamp "<< pck->getTimestamp() <<", Czas: " << simTime() << endl;
                    scheduleAt(simTime() + processDelay, processEvent);
                }
            } else {
                updateRejectedStats();
                delete pck;
            }
        } else {
            NetPacket* pck = getPacketForDeparture();

            EV << "Wyjscie: "<< pck->getName() << " Timestamp "<< pck->getTimestamp() <<", Czas: " << simTime() << endl;
            updateSendedStats(pck->getTimestamp());
            send(pck, "out");
            if (hasPacketsAwaitingDeparture())
                scheduleAt(simTime() + processDelay, processEvent);
        }
    }
}
void AbstractScheduler::handleBandwidthMessage() {
    emit(bandwidthSignal, bandwidth);
    bandwidth = 0;
    scheduleAt(simTime() + 1, emitBandwidth);
}
void AbstractScheduler::updateAcceptedStats(int64 packetSize) {
    emit(intervalSignal, simTime().dbl() - prevTime);
    timeRequestHistogram.collect(simTime());
    prevTime = simTime().dbl();
    bandwidth += packetSize;
    acceptedCount++;
}
void AbstractScheduler::updateRejectedStats() {
    emit(rejectedSignal, 1);
    rejectedCount++;
}
void AbstractScheduler::updateSendedStats(simtime_t_cref arrivalTime){
    emit(delaySignal, simTime() - arrivalTime);
    packetDelayHistogram.collect(simTime() - arrivalTime);
}
void AbstractScheduler::finish() {
    recordScalar("Rejected count", rejectedCount);
    recordScalar("Accepted count", acceptedCount);
    timeRequestHistogram.recordAs("TimeRequestHistogram");
}
