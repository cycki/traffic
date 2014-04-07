#ifndef PRIORITYADMISSIONCONTROL_H_
#define PRIORITYADMISSIONCONTROL_H_

#include "AbstractAdmissionControl.h"

class PriorityAdmissionControl : public AbstractAdmissionControl {
protected:
    uint32_t max;
    uint32_t min;

    virtual void initialize();
    virtual bool acceptMsg(NetPacket* msg);

};

#endif /* PRIORITYADMISSIONCONTROL_H_ */
