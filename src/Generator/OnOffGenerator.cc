#include "OnOffGenerator.h"

Define_Module(OnOffGenerator);

void OnOffGenerator::initialize() {
    shape = par("shape");
    scale = par("scale");
    shift = par("shift");

    AbstractGenerator::initialize();
}

simtime_t OnOffGenerator::getNextPacketCreationTime(
        simtime_t lastPacketCreationTime) {
    return lastPacketCreationTime + pareto_shifted(shape, scale, shift);
}
