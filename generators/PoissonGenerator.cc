#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <Message_m.h>
#include <Generator.h>

class PoissonGenerator : public Generator {
    private:
        double lambda;
    protected:
        virtual void handleMessage(cMessage *msg);
        virtual void initialize();
};
Define_Module(PoissonGenerator);


void PoissonGenerator::initialize(){
    lambda = par("lambda");
    Generator::initialize();
}

void PoissonGenerator::handleMessage(cMessage *msg)
{
    simtime_t time = poisson(lambda, 0);
    send(Generator::generateMessage(), "out");
    scheduleAt(simTime()+time+timeBetweenPackets, timeoutEvent);
}

