#include "AbstractScheduler.h"

void AbstractScheduler::initialize() {
    processEvent = new cMessage("processEvent");
}

void AbstractScheduler::handleMessage(cMessage* msg) {
    simtime_t processDelay = par("processDelay");

    if (msg != processEvent) {
        NetPacket* pck = check_and_cast<NetPacket*>(msg);
        bool queued = receivePacket(pck, pck->getArrivalGateId());

        if (queued) {
            if (!processEvent->isScheduled())
                scheduleAt(simTime() + processDelay, processEvent);
        } else {
            EV << "Packet " << pck->getName() << " discarded.\n";
            delete pck;
        }
    } else {
        NetPacket* pck = getPacketForDeparture();
        cGate* out = gate("out");
        cChannel* channel = out->getChannel();
        if (channel) {
            simtime_t finishTime = channel->getTransmissionFinishTime();
            simtime_t delay = std::max(finishTime - simTime(), SIMTIME_ZERO);

            sendDelayed(pck, delay, out);
        } else
            send(pck, out);
        if (hasPacketsAwaitingDeparture())
            scheduleAt(simTime() + processDelay, processEvent);
    }
}
