/*
 * OnOff.cc
 *
 *  Created on: 5 mar 2014
 *      Author: Mateusz
 */

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <Message_m.h>
#include <Generator.h>

class OnOff : public Generator {
    private:
        double lambda;
        double offTime;
        double probability;
    protected:
        virtual void handleMessage(cMessage *msg);
        virtual void initialize();
        virtual simtime_t calculateNextPacketTime();
};
Define_Module(OnOff);


void OnOff::initialize(){
    lambda = par("lambda");
    offTime = par("offTime");
    probability = par("probability");
    Generator::initialize();
}

void OnOff::handleMessage(cMessage *msg)
{
    simtime_t time = calculateNextPacketTime();
    send(Generator::generateMessage(), "out");
    scheduleAt(simTime()+time + timeBetweenPackets, timeoutEvent);
}

simtime_t OnOff::calculateNextPacketTime(){
    simtime_t time= poisson(lambda, 0);
    if(dblrand () < probability){
        time+=offTime;
    }
    return time;
}


