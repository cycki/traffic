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
    intervalEvent = new cMessage("intervalEvent");
    timeForNextPacketSending = new cMessage("timeForNextPacketSending");
}

void REDAdmissionControl::handleMessage(cMessage* msg) {
    if (msg == emitBandwidth) {
        emit(bandwidthSignal, bandwidth);
        bandwidth = 0;
        scheduleAt(simTime() + 1, emitBandwidth);
    } else {
        if (msg == intervalEvent) {
            scheduleAt(simTime() + tick, intervalEvent);
        } else {
            if (!msg->isSelfMessage()) { //jezeli pakiecik z wejcia

                NetPacket* packet = check_and_cast<NetPacket*>(msg);
                if (acceptMsg(packet)) {
                    packetQueue.push_back(packet);
                    EV << "Packet: "<< packet->getName() << " added";
                } else {
                    EV << "Packet: " << packet->getName() << " discarded"
                              << endl;
                    delete msg;
                }
            } else {//jeze
                if(packetQueue.size()>0){
                    EV << msg->getName() << " przyszlo, kolejka: "
                              << packetQueue.size() << endl;
                    NetPacket* msgToSend = packetQueue.front();
                    EV << msgToSend->getName() << " gotowe do wyslanie" <<endl;
                    //
                    packetQueue.pop_front();
                    send(msgToSend,"out");
                }


                scheduleAt(simTime() + 1, timeForNextPacketSending);
            }
        }

    }
}

bool REDAdmissionControl::acceptMsg(NetPacket* msg) {
    calculateAvgQueueLength();
    if (currentAvgQueueLength < thresholdMin) {
        EV << "Puszczam! CurrentAVG: " << currentAvgQueueLength
                  << ", currentLength: " << currentQueueLengthCount << endl;
        return true;
    } else {
        if (currentAvgQueueLength > thresholdMax) {

            EV << "Stop! CurrentAVG: " << currentAvgQueueLength
                      << ", currentLength: " << currentQueueLengthCount << endl;
            return false;
        } else {
            if (calculatePacketDropingProbability()
                    < packetDropingProbability) {

                EV << "STOp srodnie! CurrentAVG: " << currentAvgQueueLength
                          << ", currentLength: " << currentQueueLengthCount
                          << endl;
                return false;
            } else {
                EV << "Puszczam srednio! CurrentAVG: " << currentAvgQueueLength
                          << ", currentLength: " << currentQueueLengthCount
                          << endl;
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

