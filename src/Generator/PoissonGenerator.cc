#include "PoissonGenerator.h"

Define_Module(PoissonGenerator);

void PoissonGenerator::initialize() {
    poissonLambda = par("lambda");

    AbstractGenerator::initialize();
}

simtime_t PoissonGenerator::getNextPacketCreationTime(
        simtime_t lastPacketCreationTime) {
    return lastPacketCreationTime + poisson(poissonLambda, 0.1);
}
