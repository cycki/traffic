#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <Message_m.h>
#include <Generator.h>

class ExponentialGenerator : public Generator {
    private:
        double mean;
    protected:
        virtual void handleMessage(cMessage *msg);
        virtual void initialize();
};
Define_Module(ExponentialGenerator);

void ExponentialGenerator::initialize(){
        mean = par("mean");
        Generator::initialize();
}

void ExponentialGenerator::handleMessage(cMessage *msg)
{
    simtime_t time = exponential(mean, 0);
    send(Generator::generateMessage(), "out");
    scheduleAt(simTime()+time+timeBetweenPackets, timeoutEvent);
}

