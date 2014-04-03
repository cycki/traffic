#include <vector>
#include "WRR.h"

Define_Module(WRR)

void WRR::initialize() {
    AbstractScheduler::initialize();
    maxQueueSize = par("maxQueueSize");
    queuesNum = par("queuesNum");
    currentQueue = 0;

    if (queuesNum <= 0)
        throw new cRuntimeError("At least 1 queue is expected!");

    queues = new cPacketQueue*[queuesNum];
    weights = new double[queuesNum];
    credits = new double[queuesNum];

    const char* szWeights = par("weights");
    std::vector<double> vecWeights =
            cStringTokenizer(szWeights).asDoubleVector();

    if (vecWeights.size() != (uint32_t) queuesNum)
        throw new cRuntimeError(
                "Number of weights does not match number of queues!");

    double weightSum = 0;
    double minWeight = 0;
    int32_t minWeightIndex = 0;

    for (int32_t i = 0; i < queuesNum; i++) {
        cPacketQueue* queue = new cPacketQueue();
        queue->setTakeOwnership(true);

        queues[i] = queue;
        weights[i] = vecWeights[i];

        if (weights[i] <= 0)
            throw new cRuntimeError(
                    "Weights equal or below zero are not accepted!");
        weightSum += weights[i];

        if (weights[i] < minWeight) {
            minWeight = weights[i];
            minWeightIndex = i;
        }
    }

    for (int32_t i = 0; i < queuesNum; i++)
        weights[i] /= minWeight;

    weights[minWeightIndex] = 1.0;

    for (int32_t i = 0; i < queuesNum; i++)
        credits[i] = weights[i];
}

WRR:: ~WRR() {
    for (int32_t i = 0; i < queuesNum; i++)
        delete queues[i];

    delete[] queues;
    delete[] weights;
    delete[] credits;
}

bool WRR::receivePacket(NetPacket* packet,
        int gateNum) {
    int32_t priority = std::min(std::max(packet->getPriority(), 0),
            queuesNum - 1);

    if (canReceive(priority)) {
        queues[priority]->insert(packet);
        return true;
    } else
        return false;
}

bool WRR::hasPacketsAwaitingDeparture() {
    for (int32_t i = 0; i < queuesNum; i++)
        if (!queues[i]->empty())
            return true;

    return false;
}

NetPacket* WRR::getPacketForDeparture() {
    while (queues[currentQueue]->empty() || credits[currentQueue] < 1) {
        credits[currentQueue] -= (int32_t) credits[currentQueue];
        nextQueue();
    }

    credits[currentQueue] -= 1.0;

    return check_and_cast<NetPacket*>(queues[currentQueue]->pop());
}

bool WRR::canReceive(int32_t queueNum) {
    return !maxQueueSize || queues[queueNum]->getLength() < maxQueueSize;
}

void WRR::nextQueue() {
    if (++currentQueue == queuesNum) {
        currentQueue = 0;

        for (int32_t i = 0; i < queuesNum; i++)
            credits[i] += weights[i];
    }
}
