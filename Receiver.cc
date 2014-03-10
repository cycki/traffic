#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <Message_m.h>

/**
 * Sends back an acknowledgement -- or not.
 */
class Receiver : public cSimpleModule
{

    private:
        cLongHistogram timeStats;
        cOutVector timeVector;
        simtime_t previousTime;
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();
};

Define_Module(Receiver);
void Receiver::initialize(){
    previousTime = simTime();
}

void Receiver::handleMessage(cMessage *msg)
{
    EV << "Message: ";
    EV << msg->getName() << endl;
    timeVector.record(simTime()-previousTime);
    timeStats.collect(simTime()-previousTime);
    previousTime = simTime();
    delete msg;
}

void Receiver::finish()
{
    timeStats.recordAs("Histogram");
}
