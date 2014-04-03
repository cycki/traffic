#include "AbstractProfiler.h"

void AbstractProfiler::initialize() {
    maxQueueSize = par("maxQueueSize");
    bandwidthEvent = new cMessage("bandwidthEvent");
    inputSignal = registerSignal("Input");
    outputSignal = registerSignal("Output");
    bandwidthCalcTick = par("bandwidthCalcTick");
    endTime = par("endTime");
    inputBandwidthSum = 0;
    outputBandwidthSum = 0;
    inputBandwidth = 0;
    outputBandwidth = 0;
    emit(inputSignal, inputBandwidth);
    emit(outputSignal, outputBandwidth);
    scheduleAt(SIMTIME_ZERO, bandwidthEvent);
    WATCH(inputBandwidth);
    WATCH(outputBandwidth);
}

void AbstractProfiler::handleMessage(cMessage* msg) {
    if (msg == bandwidthEvent) {
        calcMeanBandwidth();
        simtime_t currentTime = simTime();
        if (currentTime < endTime || endTime == 0 || !queue.empty())
            scheduleAt(currentTime + bandwidthCalcTick, bandwidthEvent);
        else {
            inputBandwidth = 0;
            outputBandwidth = 0;
            delete bandwidthEvent;
        }
    } else {
        NetPacket* pck = check_and_cast<NetPacket*>(msg);

        if (!pck->isSelfMessage()) {
            inputBandwidthSum += pck->getByteLength();
            if (canReceive()) {
                if (queue.empty()) {
                    simtime_t processDelay = par("processDelay");
                    scheduleAt(simTime() + processDelay, pck);
                }
                queue.push_back(pck);
            } else {
                EV << "Packet " << pck->getName() << " discarded.\n";
                delete pck;
            }
        } else {
            simtime_t delay;
            if (acceptPacket(pck, delay)) {
                queue.pop_front();
                cGate* out = gate("out");
                cChannel* channel = out->getChannel();
                if (channel) {
                    simtime_t finishTime = channel->getTransmissionFinishTime();
                    simtime_t delay = std::max(finishTime - simTime(),
                    SIMTIME_ZERO);

                    sendDelayed(pck, delay, out);
                } else
                    send(pck, out);
                    outputBandwidthSum += pck->getByteLength();
                if (!queue.empty()) {
                    //simtime_t processDelay = par("processDelay");
                    scheduleAt(simTime() /*+ processDelay*/, queue.front());
                }
            } else {
                //simtime_t processDelay = par("processDelay");
                scheduleAt(simTime() + delay/* + processDelay*/, pck);
            }
        }
    }
}

bool AbstractProfiler::canReceive() {
    return queue.size() < maxQueueSize || !maxQueueSize;
}

void AbstractProfiler::calcMeanBandwidth() {
    inputBandwidth = inputBandwidthSum / bandwidthCalcTick.dbl();
    outputBandwidth = outputBandwidthSum / bandwidthCalcTick.dbl();

    emit(inputSignal, inputBandwidth);
    emit(outputSignal, outputBandwidth);

    inputBandwidthSum = 0;
    outputBandwidthSum = 0;
}
