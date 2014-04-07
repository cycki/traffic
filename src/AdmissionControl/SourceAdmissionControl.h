#ifndef SOURCEADMISSIONCONTROL_H_
#define SOURCEADMISSIONCONTROL_H_

#include "AbstractAdmissionControl.h"
#include <set>
class SourceAdmissionControl : public AbstractAdmissionControl {
protected:
    std::set<uint32_t> BlockedSources;

    virtual void initialize();
    virtual bool acceptMsg(NetPacket* msg);

};

#endif /* SOURCEADMISSIONCONTROL_H_ */
