#include <WRRScheduler.h>
Define_Module(WRRScheduler);

void WRRScheduler::initialize() {
    AbstractScheduler::initialize();
    packetsToBeSendFromCurrentQueue = 0;
    currentQueue = 0;
    maxQueueSize = par("maxQueueSize");
    const char* szWeights = par("weights");
    std::vector<double> vecWeights =
            cStringTokenizer(szWeights, ";").asDoubleVector();
    meanPacketSize = par("meanPacketSize");

    for (int i = 0; i < gateSize("in"); i++) {
        awaitingPackets.push_back(new WRRQueue(meanPacketSize, vecWeights[i]));
        EV << "Mean: " << meanPacketSize << " waga: " << vecWeights[i] << endl;
    }

    double min = awaitingPackets[0]->normalizedWeight;
    for (int i = 1; i < gateSize("in"); i++) {
        if (min > awaitingPackets[i]->normalizedWeight) {
            min = awaitingPackets[i]->normalizedWeight;
        }
    }
    EV << "Obliczone min: " << min << endl;
    for (int i = 0; i < gateSize("in"); i++) {
        awaitingPackets[i]->setPacketsToBeServed(min);
    }

}

bool WRRScheduler::receivePacket(NetPacket* packet, int gateNum) {
    int gateNumber = gateNum % gateSize("in");
    if (canReceive(gateNumber )) {
        awaitingPackets[gateNumber]->addPacket(packet);
        return true;
    } else {
        return false;
    }
}

bool WRRScheduler::canReceive(int gateNum) {
    int gateNumber =  gateNum % gateSize("in");
    return awaitingPackets[gateNumber]->size() < (int) maxQueueSize
            || !maxQueueSize;
}

bool WRRScheduler::hasPacketsAwaitingDeparture() {
    for (int i = 0; i < (int) awaitingPackets.size(); i++) {
        if (!(awaitingPackets[i])->isEmpty()) {
            return true;
        }
    }
    return false;
}

NetPacket* WRRScheduler::getPacketForDeparture() {
    //jezeli jeszcze nie obsluzyles tej kolejki - wyslij z niej pakiet
    int gateSizeNumber = gateSize("in");
    if (packetsToBeSendFromCurrentQueue > 0) {
        if (packetsToBeSendFromCurrentQueue
                > awaitingPackets[currentQueue]->size()) {
            //ale nie wysylaj wiecej ni¿ mo¿esz;
            packetsToBeSendFromCurrentQueue =
                    awaitingPackets[currentQueue]->size();
        }
    } else { //zmien kolejke, ustaw ze mozesz wyslac nowa ilosc pakietow;
        for (int i = 0; i < gateSizeNumber; i++) {
            if (!awaitingPackets[currentQueue]->isEmpty()) {
                break;
            }
            currentQueue = (currentQueue + 1) % gateSizeNumber;
        }

        packetsToBeSendFromCurrentQueue = std::min(
                awaitingPackets[currentQueue]->packetsToBeServed,
                awaitingPackets[currentQueue]->size());
    }

    packetsToBeSendFromCurrentQueue--;

    NetPacket* pck = awaitingPackets[currentQueue]->getPacket();
    return pck;
}
