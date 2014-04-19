#include "AbstractProfiler.h"

void AbstractProfiler::initialize() {
    bandwidthCalcTick = par("bandwidthCalcTick");
    maxQueueSize = par("maxQueueSize");
    endTime = par("endTime");
    initializeStatistics();
}

void AbstractProfiler::initializeStatistics() {
    inputBandwidthSum = 0;
    outputBandwidthSum = 0;
    inputBandwidth = 0;
    outputBandwidth = 0;
    rejectedCount = 0;
    acceptedCount = 0;
    WATCH(inputBandwidth);
    WATCH(outputBandwidth);
    bandwidthEvent = new cMessage("bandwidthEvent");
    scheduleAt(SIMTIME_ZERO, bandwidthEvent);
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
        NetPacket* packet = check_and_cast<NetPacket*>(msg);

        // Pakiet pojawil sie na wejsciu
        if (!packet->isSelfMessage()) {
            inputBandwidthSum += packet->getByteLength();
            if (canReceive()) { //jezeli jest miejsce - zakolejkowanie pakietu
                acceptedCount++;
                packet->setTimestamp();
                if (queue.empty()) {
                    simtime_t processDelay = par("processDelay");
                    scheduleAt(simTime() + processDelay, packet); //wyslanie komunikatu do siebie o zdarzeniu
                }
                queue.push_back(packet);
            } else {
                rejectedCount++;
                delete packet;
            }
        } else { //Obsluga zdarzenia wlasnego
            simtime_t delay;
            if (acceptPacket(packet, delay)) { //Akceptowanie pakietu zalezne od zastosowanego algorytmu,
                queue.pop_front(); //usuwamy zaakceptowany do wyjcia pakiet z kolejki oczekujacych
                send(packet, "out"); //wysylamy go na wyjscie
                packetDelayHistogram.collect(simTime() - packet->getTimestamp());
                outputBandwidthSum += packet->getByteLength(); //aktualizacja statystyk
                if (!queue.empty()) { //jezeli sa jeszcze elementy w kolejce ustawiamy zdarzenie do wyslanie pierwszego z kolejki
                    scheduleAt(simTime(), queue.front());
                }
            } else { //jezeli algorytm ksztaltujacy nie pozwolil na wyslanie pakietu
                scheduleAt(simTime() + delay, packet); //ustawiamy zdarze z obliczonym opoznieniem
            }
        }
    }
}

bool AbstractProfiler::canReceive() {
    return queue.size() < maxQueueSize || !maxQueueSize;
}

void AbstractProfiler::finish() {
    recordScalar("Rejected count", rejectedCount);
    recordScalar("Accepted count", acceptedCount);
    outputQueueHistogram.recordAs("Profiler Output");
    inputQueueHistogram.recordAs("Profiler Input");
    packetDelayHistogram.recordAs("Packet delay");
}

void AbstractProfiler::calcMeanBandwidth() {
    inputBandwidth = inputBandwidthSum / bandwidthCalcTick.dbl();
    outputBandwidth = outputBandwidthSum / bandwidthCalcTick.dbl();

    inputQueueHistogram.collect(inputBandwidth);
    outputQueueHistogram.collect(outputBandwidth);
    inputBandwidthSum = 0;
    outputBandwidthSum = 0;
}
