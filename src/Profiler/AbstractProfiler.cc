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
    inputSignal = registerSignal("Input");
    outputSignal = registerSignal("Output");
    emit(inputSignal, inputBandwidth);
    emit(outputSignal, outputBandwidth);
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
                if (queue.empty()) {
                    simtime_t processDelay = par("processDelay");
                    scheduleAt(simTime() + processDelay, packet); //wyslanie komunikatu do siebie o zdarzeniu
                }
                queue.push_back(packet);
            } else {
                delete packet;
            }
        } else { //Obsluga zdarzenia wlasnego
            simtime_t delay;
            if (acceptPacket(packet, delay)) { //Akceptowanie pakietu zalezne od zastosowanego algorytmu,
                queue.pop_front(); //usuwamy zaakceptowany do wyjcia pakiet z kolejki oczekujacych
                send(packet, "out"); //wysylamy go na wyjscie
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

void AbstractProfiler::calcMeanBandwidth() {
    inputBandwidth = inputBandwidthSum / bandwidthCalcTick.dbl();
    outputBandwidth = outputBandwidthSum / bandwidthCalcTick.dbl();

    emit(inputSignal, inputBandwidth);
    emit(outputSignal, outputBandwidth);

    inputBandwidthSum = 0;
    outputBandwidthSum = 0;
}
