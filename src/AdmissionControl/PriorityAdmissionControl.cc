#include "PriorityAdmissionControl.h"

Define_Module(PriorityAdmissionControl)

void PriorityAdmissionControl::initialize(){

    AbstractAdmissionControl::initialize();

    maxPriority = par ("Maximal_priority");
    minPriority = par ("Minimal_priority");

}

bool PriorityAdmissionControl::acceptMsg(NetPacket *msg){
    uint32_t prior = msg->getPriority();

    return prior<=this->maxPriority&&prior>=this->minPriority;

}
