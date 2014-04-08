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

#include <WRRScheduler.h>
Define_Module(WRRScheduler);

void WRRScheduler::initialize() {
    AbstractScheduler::initialize();
    packetsToBeSendFromCurrentQueue = 0;
    maxQueueSize = par("maxQueueSize");
    const char* szWeights = par("weights");
    std::vector<double> vecWeights =
            cStringTokenizer(szWeights, ";").asDoubleVector();
    meanPacketSize = par("meanPacketSize");

    for (int i = 0; i < gateSize("in"); i++) {
        awaitingPackets.push_back(new WRRQueue(meanPacketSize, vecWeights[i]));
        EV << "Mean: " << meanPacketSize << " waga: " << vecWeights[i] << endl;
    }

    double min = awaitingPackets[0]->normalizedWeight;
    for (int i = 1; i < gateSize("in"); i++) {
        if (min > awaitingPackets[i]->normalizedWeight) {
            min = awaitingPackets[i]->normalizedWeight;
        }
    }
    EV << "Obliczone min: " << min << endl;
    for (int i = 0; i < gateSize("in"); i++) {
        awaitingPackets[i]->setPacketsToBeServed(min);
    }

}

bool WRRScheduler::receivePacket(NetPacket* packet, int gateNum) {
    if (canReceive(gateNum % gateSize("in"))) {
        awaitingPackets[gateNum % gateSize("in")]->addPacket(packet);
        return true;
    } else {
        return false;
    }
}

bool WRRScheduler::canReceive(int gateNum) {
    return awaitingPackets[gateNum % 6]->size() < (int) maxQueueSize
            || !maxQueueSize;
}

bool WRRScheduler::hasPacketsAwaitingDeparture() {
    for (int i = 0; i < (int) awaitingPackets.size(); i++) {
        if (!(awaitingPackets[i])->isEmpty()) {
            return true;
        }
    }
    return false;
}

NetPacket* WRRScheduler::getPacketForDeparture() {
    //jezeli jeszcze nie obsluzyles tej kolejki - wyslij z niej pakiet
    if (packetsToBeSendFromCurrentQueue > 0) {
        if (packetsToBeSendFromCurrentQueue
                > awaitingPackets[currentQueue]->size()) {
            //ale nie wysylaj wiecej ni¿ mo¿esz;
            packetsToBeSendFromCurrentQueue =
                    awaitingPackets[currentQueue]->size();
        }
    } else { //zmien kolejke, ustaw ze mozesz wyslac nowa ilosc pakietow;
        for (int i = 0; i < gateSize("in"); i++) {
            if (!awaitingPackets[currentQueue]->isEmpty()) {
                break;
            }
            currentQueue = (currentQueue + 1) % gateSize("in");
        }
        packetsToBeSendFromCurrentQueue = std::min(
                awaitingPackets[currentQueue]->packetsToBeServed,
                awaitingPackets[currentQueue]->size());
    }

    packetsToBeSendFromCurrentQueue--;

    NetPacket* pck = awaitingPackets[currentQueue]->getPacket();
    return pck;
}
