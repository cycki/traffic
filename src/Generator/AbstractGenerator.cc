#include "AbstractGenerator.h"

int AbstractGenerator::totalNumGen = 0;

void AbstractGenerator::initialize() {
    intervalSignal = registerSignal("interval");
    intervalEvent = new cMessage("intervalEvent");

    simtime_t packetSendTime = getNextPacketCreationTime(0);

    end = par("end");

    WATCH("end");

    emit(intervalSignal, packetSendTime);

    scheduleAt(packetSendTime, intervalEvent);

    sessionId = &par("sessionId");

    lowerPriority = par("lowerPriority");
    upperPriority = par("upperPriority");
    lowerSessionId = par("lowerSessionId");
    upperSessionId = par("upperSessionId");
    meanLength = par("meanLength");
    stdDevLength = par("stdDevLength");
}

void AbstractGenerator::handleMessage(cMessage* msg) {
    simtime_t currentTime = simTime();
    if (msg == intervalEvent && (currentTime < end || end == 0)) {
        cGate* out = gate("out");

        send(generatePacket(), out);

        simtime_t nextSendTime = getNextPacketCreationTime(currentTime);

        emit(intervalSignal, nextSendTime - currentTime);

        scheduleAt(nextSendTime, intervalEvent);
    } else
        delete msg;
}

NetPacket* AbstractGenerator::generatePacket() {
    char packetName[20];
    totalNumGen++;
    sprintf(packetName, "pckt-%d", totalNumGen);


    NetPacket* pckt = new NetPacket(packetName);
    pckt->setSrc(getId());
    pckt->setPacketId(totalNumGen);
    pckt->setPriority(intuniform(lowerPriority, upperPriority));
    pckt->setByteLength(truncnormal(meanLength, stdDevLength));
    pckt->setStartTime(simTime().dbl());
    pckt->setSessionId(intuniform(lowerSessionId, upperSessionId));

    return pckt;
}
