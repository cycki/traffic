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
		
		// Pakiet pojawil sie na wejsciu
        if (!pck->isSelfMessage()) {
            inputBandwidthSum += pck->getByteLength();
            if (canReceive()) {//jezeli jest miejsce - zakolejkowanie pakietu
                if (queue.empty()) {
                    simtime_t processDelay = par("processDelay");
                    scheduleAt(simTime() + processDelay, pck);//wyslanie komunikatu do siebie o zdarzeniu
                }
                queue.push_back(pck);
            } else {
                EV << "Packet " << pck->getName() << " discarded.\n";
                delete pck;
            }
        } else {//Obsluga zdarzenia wlasnego
            simtime_t delay;
            if (acceptPacket(pck, delay)) {//Akceptowanie pakietu zalezne od zastosowanego algorytmu,
                queue.pop_front();//usuwamy zaakceptowany do wyjcia pakiet z kolejki oczekujacych
                send(pck, "out");//wysylamy go na wyjscie
                outputBandwidthSum += pck->getByteLength(); //aktualizacja statystyk
                if (!queue.empty()) {//jezeli s¹ jeszcze elementy w kolejce ustawiamy zdarzenie do wyslanie pierwszego z kolejki
                    scheduleAt(simTime(), queue.front());
                }
            } else {//jezeli algorytm ksztaltujacy nie pozwolil na wyslanie pakietu
                scheduleAt(simTime() + delay, pck);//ustawiamy zdarze z obliczonym opoznieniem
            }
        }
    }
}

bool AbstractProfiler::canReceive() {
    return queue.size() < maxQueueSize || !maxQueueSize;
}

// Sprawdz przepustowsc
void AbstractProfiler::calcMeanBandwidth() {
    inputBandwidth = inputBandwidthSum / bandwidthCalcTick.dbl();
    outputBandwidth = outputBandwidthSum / bandwidthCalcTick.dbl();

    emit(inputSignal, inputBandwidth);
    emit(outputSignal, outputBandwidth);

    inputBandwidthSum = 0;
    outputBandwidthSum = 0;
}
