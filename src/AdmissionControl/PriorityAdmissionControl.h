#ifndef PRIORITYADMISSIONCONTROL_H_
#define PRIORITYADMISSIONCONTROL_H_

#include "AbstractAdmissionControl.h"

class PriorityAdmissionControl : public AbstractAdmissionControl {
protected:
    uint32_t minPriority;
    uint32_t maxPriority;

    virtual void initialize();
    virtual bool acceptMsg(NetPacket* msg);

};

#endif /* PRIORITYADMISSIONCONTROL_H_ */
