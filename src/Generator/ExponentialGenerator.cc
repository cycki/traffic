#include "ExponentialGenerator.h"

Define_Module(ExponentialGenerator);

void ExponentialGenerator::initialize()
{
    exponentialMean = par("mean");

    AbstractGenerator::initialize();
}

simtime_t ExponentialGenerator::getNextPacketCreationTime(simtime_t lastPacketCreationTime)
{
    return lastPacketCreationTime + exponential(exponentialMean);
}
