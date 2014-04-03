#include "RR.h"

Define_Module(RR)



bool RR::receivePacket(NetPacket* packet, int gn) {

    int prio = packet->getPriority();

    int num = 0;
    for (std::list<int>::iterator iter = priorList.begin();
            (*iter) < prio && iter != priorList.end(); ++iter)
        num++;
    std::list<list<NetPacket*>*>::iterator element = packetList.begin();
    while (num-- > 0)
        element++;
    (*element)->push_back(packet);
    packetSum++;

    return true;
}

NetPacket* RR::getPacketForDeparture() {
    NetPacket* ref;
    if (packetSum > 0) {
        std::list<list<NetPacket*>*>::iterator element = packetList.begin();
        ++currentQueue;
        if (currentQueue >= priorList.size()) {
            currentQueue = 0;
            element = packetList.begin();
        } else {
            int cq = currentQueue;
            while (cq-- > 0)
                element++;
        }
        while ((*element)->empty()) {
            element++;
            currentQueue++;
            if (currentQueue >= priorList.size()) {
                currentQueue = 0;
                element = packetList.begin();
            }
        }
        ref = (*element)->front();
        (*element)->pop_front();
        packetSum--;
    }
    return ref;
}

void RR::initialize() {
    AbstractScheduler::initialize();
    packetSum = 0;
    currentQueue = -1;
    WATCH(packetSum);
    WATCH(currentQueue);
    WATCH_LIST(priorList);
    maxQueueSize = par("maxQueueSize");


    int ql = par("queueLength");
    int max = par("maxPriority");
    if (ql > max)
        ql = max;
    double up = (double) max / (double) ql;
    for (int i = 0; i < ql - 1; i++) {
        priorList.push_back((int) ((i + 1) * up));
        packetList.push_back(new std::list<NetPacket*>());
    }
    packetList.push_back(new std::list<NetPacket*>());
    priorList.push_back(1000);

}

bool RR::hasPacketsAwaitingDeparture() {
    return packetSum > 0 && packetSum < maxQueueSize;
}
