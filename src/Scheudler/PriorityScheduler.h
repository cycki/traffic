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

#ifndef PRIORITYSCHEDULER_H_
#define PRIORITYSCHEDULER_H_

#include <omnetpp.h>
#include <queue>
#include <vector>
#include "AbstractScheduler.h"
class ComparePriority {
public:
    bool operator()(NetPacket*& m1, NetPacket*& m2) {
                    return m1->getPriority() > m2->getPriority();
    }
};

class PriorityScheduler : public AbstractScheduler {
    protected:
        virtual void initialize();
        virtual bool receivePacket(NetPacket* packet, int gateNum);
        virtual bool hasPacketsAwaitingDeparture();
        virtual NetPacket* getPacketForDeparture();
    private:
        bool canReceive();
    public:
        unsigned maxQueueSize;
        std::priority_queue<NetPacket*, std::vector<NetPacket*>, ComparePriority> awaitingPackets;


};

#endif /* PRIORITYSCHEDULER_H_ */
