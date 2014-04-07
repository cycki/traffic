
#include "AbstractAdmissionControl.h"

void AbstractAdmissionControl::initialize() {
    cMessage* msg = new cMessage("intervalEvent");
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
    tick = 5;
    scheduleAt(simTime(), msg);
    scheduleAt(simTime() + 1, emitBandwidth);
}

void AbstractAdmissionControl::handleMessage(cMessage* msg) {
    if (msg == emitBandwidth) {
        emit(bandwidthSignal, bandwidth);
        bandwidth = 0;
        scheduleAt(simTime() + 1, emitBandwidth);
    } else {
        if (msg->isSelfMessage())
        {
            delete msg;
            cMessage* msg2 = new cMessage("intervalEvent");
            scheduleAt(simTime() + tick, msg2);
        } else {
            NetPacket* packet = check_and_cast<NetPacket*>(msg);
            if (acceptMsg(packet)) {
                emit(intervalSignal, simTime().dbl() - prevTime);
                timeRequestHistogram.collect(simTime());
                prevTime = simTime().dbl();
                emit(delaySignal, simTime() - packet->getArrivalTime());
                bandwidth += packet->getByteLength();
                acceptedCount++;
                send(packet, "out");
            } else {
                emit(rejectedSignal, 1);
                rejectedCount++;
                delete packet;
            }
        }
    }
}

void AbstractAdmissionControl::finish() {
    recordScalar("Rejected count", rejectedCount);
    recordScalar("Accepted count", acceptedCount);
    timeRequestHistogram.recordAs("TimeRequestHistogram");
}
