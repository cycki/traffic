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
