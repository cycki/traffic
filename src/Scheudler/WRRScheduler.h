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

#ifndef WRRSCHEDULER_H_
#define WRRSCHEDULER_H_


#include "AbstractScheduler.h"
#include <vector>
#include <queue>

class WRRQueue {
public:
    double normalizedWeight;
    int packetsToBeServed;
    std::queue<NetPacket*> packetQueue;
private:
    double weight;
    double meanPacketSize;
public:
    void addPacket(NetPacket* p){
        packetQueue.push(p);
    }
    NetPacket* getPacket(){
        NetPacket* packet = packetQueue.front();
        packetQueue.pop();
        return packet;
    }
    bool isEmpty(){
        return packetQueue.empty();
    }
    WRRQueue(int  meanSize, double queueWeight){
        meanPacketSize = meanSize;
        weight = queueWeight;
        normalizedWeight = weight / meanPacketSize;
        packetsToBeServed=0;
    };
    void setPacketsToBeServed(double min){
        packetsToBeServed = (int)(normalizedWeight/min);
    }
    int size(){
        return packetQueue.size();
    }
};

class WRRScheduler : public AbstractScheduler{
protected:
        virtual void initialize();
        virtual bool receivePacket(NetPacket* packet, int gateNum);
        virtual bool hasPacketsAwaitingDeparture();
        virtual NetPacket* getPacketForDeparture();
        bool canReceive(int gateNum);
        uint32_t maxQueueSize;
        std::vector<WRRQueue* > awaitingPackets;
    private:
        int packetsToBeSendFromCurrentQueue;
        double meanPacketSize;
        int currentQueue;
};

#endif /* WRRSCHEDULER_H_ */
