#include <omnetpp.h>
#include "Message_m.h"
#include "AbstractScheduler.h"
#include <list>

class LifoScheduler: public AbstractScheduler {

    protected:
        uint32_t maxQueueSize;
        std::list<Message*> awaitingPackets;

        cOutVector queueVector;

        virtual void initialize();
        virtual bool receivePacket(Message* packet, int gateNum);
        virtual bool hasPacketsAwaitingDeparture();
        virtual Message* getPacketForDeparture();
        bool canReceive();
};

Define_Module(LifoScheduler);

void LifoScheduler::initialize(){
    AbstractScheduler::initialize();
    maxQueueSize = par("maxQueueSize");
    queueVector.setName("Ilosc plikow w kolejce LIFO");
}

bool LifoScheduler::receivePacket(Message* packet, int gateNum)
{
        queueVector.record(awaitingPackets.size());
        if(canReceive())
        {
                awaitingPackets.push_back(packet);
                EV << "Packet " << packet->getName() << " added to list."<<endl;
                EV << "List size: " << awaitingPackets.size() << endl;
                return true;
        }
        else{
            return false;
        }
}

bool LifoScheduler::hasPacketsAwaitingDeparture()
{
        return !awaitingPackets.empty();
}

Message* LifoScheduler::getPacketForDeparture()
{
        Message* pck = awaitingPackets.back();
        awaitingPackets.pop_back();
        EV << "List size: " << awaitingPackets.size() << endl;
        queueVector.record(awaitingPackets.size());
        return pck;
}

bool LifoScheduler::canReceive()
{
        return awaitingPackets.size() < maxQueueSize || !maxQueueSize;
}



