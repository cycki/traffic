#include <PriorityScheduler.h>

Define_Module(PriorityScheduler)

void PriorityScheduler::initialize() {
    AbstractScheduler::initialize();
    maxQueueSize = par("maxQueueSize");
}

bool PriorityScheduler::receivePacket(NetPacket* packet, int gateNum)
{
    if(canReceive())
    {
        awaitingPackets.push(packet);
        return true;
    }
    else{
        return false;
    }
}

bool PriorityScheduler::hasPacketsAwaitingDeparture()
{
    return !awaitingPackets.empty();
}

NetPacket* PriorityScheduler::getPacketForDeparture()
{
    NetPacket* pck = awaitingPackets.top();
    awaitingPackets.pop();

    return pck;
}

bool PriorityScheduler::canReceive()
{
    return awaitingPackets.size() < maxQueueSize || !maxQueueSize;
}
