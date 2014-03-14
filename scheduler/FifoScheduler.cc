#include <omnetpp.h>
#include "Message_m.h"
#include "AbstractScheduler.h"
#include <list>

class FifoScheduler: public AbstractScheduler {

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

Define_Module(FifoScheduler);

void FifoScheduler::initialize(){
    AbstractScheduler::initialize();
    maxQueueSize = par("maxQueueSize");
    queueVector.setName("Ilosc plikow w kolejce Fifo");
}

bool FifoScheduler::receivePacket(Message* packet, int gateNum)
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

bool FifoScheduler::hasPacketsAwaitingDeparture()
{
        return !awaitingPackets.empty();
}

Message* FifoScheduler::getPacketForDeparture()
{
        Message* pck = awaitingPackets.front();
        awaitingPackets.pop_front();
        EV << "List size: " << awaitingPackets.size() << endl;
        queueVector.record(awaitingPackets.size());
        return pck;
}

bool FifoScheduler::canReceive()
{
        return awaitingPackets.size() < maxQueueSize || !maxQueueSize;
}



