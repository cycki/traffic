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

#ifndef RRSCHEDULER_H_
#define RRSCHEDULER_H_

#include "AbstractScheduler.h"
#include <vector>
#include <queue>
/**
 * Posiada listy kolejek dla ka�dego z wejsc.
 * Co cykl zmienia kolejk� (wejscie) z kt�rej bierze pakiet. Puste kolejki pomija
 */
class RRScheduler : public AbstractScheduler{
    protected:
        virtual void initialize();
        virtual bool receivePacket(NetPacket* packet, int gateNum);
        virtual bool hasPacketsAwaitingDeparture();
        virtual NetPacket* getPacketForDeparture();
        bool canReceive(int gateNum);
        uint32_t maxQueueSize;
        std::vector<std::queue<NetPacket*>* > awaitingPackets;
    private:
        int currentQueue;
};

#endif /* RRSCHEDULER_H_ */
