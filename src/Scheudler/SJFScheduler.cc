#include <SJFScheduler.h>


Define_Module(SJFScheduler);

void SJFScheduler::initialize() {
    AbstractScheduler::initialize();
    maxQueueSize = par("maxQueueSize");
}

bool SJFScheduler::receivePacket(NetPacket* packet, int gateNum)
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

bool SJFScheduler::hasPacketsAwaitingDeparture()
{
    return !awaitingPackets.empty();
}

NetPacket* SJFScheduler::getPacketForDeparture()
{
    NetPacket* pck = awaitingPackets.top();
    awaitingPackets.pop();

    return pck;
}

bool SJFScheduler::canReceive()
{
    return awaitingPackets.size() < maxQueueSize || !maxQueueSize;
}
