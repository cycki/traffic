#include "SourceAdmissionControl.h"

Define_Module(SourceAdmissionControl)

void SourceAdmissionControl::initialize()
{
	AbstractAdmissionControl::initialize();
	deny = par("deny");
}

bool SourceAdmissionControl::acceptMsg(NetPacket* msg)
{
    return !((uint32_t)msg->getSrc() == this->deny);
}
