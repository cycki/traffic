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

#include <RedAdmissionCotrol.h>

Define_Module(REDAdmissionControl);

void REDAdmissionControl::initialize() {
    AbstractAdmissionControl::initialize();
    thresholdMin = par("thresholdMin");
    thresholdMax = par("thresholdMax");
    packetDropingProbability = par("packetDropingProbability");
    currentAvgQueueLength = 0;
    currentQueueLengthCount = 0;
    timeForNextPacketSending = new cMessage("timeForNextPacketSending");
    scheduleAt(simTime(), timeForNextPacketSending);
}

void REDAdmissionControl::handleMessage(cMessage* msg) {
    if (msg == emitBandwidth) {
        emit(bandwidthSignal, bandwidth);
        bandwidth = 0;
        scheduleAt(simTime() + 1, emitBandwidth);
    } else {
        if (!msg->isSelfMessage()) { //jezeli pakiecik z wejcia

            NetPacket* packet = check_and_cast<NetPacket*>(msg);
            if (acceptMsg(packet)) {
                packetQueue.push_back(packet);
                //troche statystyk
                emit(intervalSignal, simTime().dbl() - prevTime);
                timeRequestHistogram.collect(simTime());
                prevTime = simTime().dbl();
                emit(delaySignal, simTime() - packet->getArrivalTime());
                bandwidth += packet->getByteLength();
                acceptedCount++;
            } else {
                emit(rejectedSignal, 1);
                rejectedCount++;
                delete msg;
            }
        } else {
            if (packetQueue.size() > 0) {
                NetPacket* msgToSend = packetQueue.front();
                packetQueue.pop_front();
                send(msgToSend, "out");
            }
            if(!timeForNextPacketSending->isScheduled())
                scheduleAt(simTime() + tick, timeForNextPacketSending);
        }

    }
}

bool REDAdmissionControl::acceptMsg(NetPacket* msg) {
    calculateAvgQueueLength();
    if (currentAvgQueueLength < thresholdMin) {
        return true;
    } else {
        if (currentAvgQueueLength > thresholdMax) {
            return false;
        } else {
            if (calculatePacketDropingProbability()
                    < packetDropingProbability) {
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}

void REDAdmissionControl::calculateAvgQueueLength() {
    double sum = currentAvgQueueLength * currentQueueLengthCount;
    sum += packetQueue.size();
    currentQueueLengthCount++;
    currentAvgQueueLength = sum / (double) currentQueueLengthCount;
}

double REDAdmissionControl::calculatePacketDropingProbability() {
    return uniform(0, 1, 0);
}

