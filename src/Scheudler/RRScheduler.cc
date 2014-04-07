#include <RRScheduler.h>

Define_Module(RRScheduler);

void RRScheduler::initialize() {
    AbstractScheduler::initialize();
    maxQueueSize = par("maxQueueSize");
    currentQueue = 0;
    for(int i=0;i<gateSize("in");i++){
        awaitingPackets.push_back(new std::queue<NetPacket*>());
    }
}

bool RRScheduler::receivePacket(NetPacket* packet, int gateNum) {
    if(canReceive(gateNum%gateSize("in")))
    {
            awaitingPackets[gateNum%gateSize("in")]->push(packet);
            return true;
    }
    else{
        return false;
    }
}

bool RRScheduler::canReceive(int gateNum) {
    return awaitingPackets[gateNum%6]->size() < maxQueueSize || !maxQueueSize;
}

bool RRScheduler::hasPacketsAwaitingDeparture() {
    for(int i=0;i<(int)awaitingPackets.size();i++){
        if(!(awaitingPackets[i])->empty()){
            return true;
        }
    }
    return false;
}

NetPacket* RRScheduler::getPacketForDeparture() {

    for(int i=0; i<gateSize("in"); i++){
        currentQueue++;
        currentQueue = currentQueue%gateSize("in");
        if(!awaitingPackets[currentQueue]->empty()){
            break;
        }
    }
    NetPacket* pck = awaitingPackets[currentQueue]->front();
    awaitingPackets[currentQueue]->pop();
    return pck;
}
