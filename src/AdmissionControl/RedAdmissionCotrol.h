//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef REDADMISSIONCOTROL_H_
#define REDADMISSIONCOTROL_H_

#include <AbstractAdmissionControl.h>
#include <list>

class REDAdmissionControl : public AbstractAdmissionControl {
protected:
    void initialize();
    bool acceptMsg(NetPacket* packet);
    void handleMessage(cMessage* msg);
    double thresholdMin;
    double thresholdMax;

private:
    double currentAvgQueueLength;
    int currentQueueLengthCount;
    double packetDropingProbability;
    cMessage* timeForNextPacketSending;
    cMessage* intervalEvent;
    std::list<NetPacket*> packetQueue;
    void calculateAvgQueueLength();
    double calculatePacketDropingProbability();
};

#endif /* REDADMISSIONCOTROL_H_ */
