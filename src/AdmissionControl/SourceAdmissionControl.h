#ifndef SOURCEADMISSIONCONTROL_H_
#define SOURCEADMISSIONCONTROL_H_


#include "AbstractAdmissionControl.h"


class SourceAdmissionControl : public AbstractAdmissionControl
{
protected:
    uint32_t deny;

	virtual void initialize();
	virtual bool acceptMsg(NetPacket* msg);
};

#endif /* SOURCEADMISSIONCONTROL_H_ */
