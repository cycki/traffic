#include "TokenBucket.h"

Define_Module(TokenBucket)

void TokenBucket::initialize() {
    AbstractProfiler::initialize();
    tokens = 0;
    BUCKET_CAPACITY = par("tokensMax");
    tokenIncrement = par("tokenIncrement");
    lastTokenIncrement = SIMTIME_ZERO;
    lastDelayedPacket = NULL;
    WATCH(tokens);
}

bool TokenBucket::acceptPacket(NetPacket* packet, simtime_t& delay) {
    simtime_t currentTime = simTime();
    simtime_t timeDiff = currentTime - lastTokenIncrement;

    if (timeDiff > 0) {
        tokens = std::min((int32_t) (tokens + tokenIncrement * timeDiff.dbl()), BUCKET_CAPACITY);
    }
    lastTokenIncrement = currentTime;

	// Jeśli to ostatni opóźniony pakiet
    if (packet == lastDelayedPacket) {
        return true;
    }
	// Jeśli wielkość pakietu odpowiada ilości tokenów
    else if (packet->getByteLength() <= tokens) {
        tokens -= packet->getByteLength();
        return true;
	// W przeciwnym wypadku pakiet zostaje opóźniony
    } else {
        lastDelayedPacket = packet;
        delay = (double) (packet->getByteLength() - tokens) / tokenIncrement;
        tokens -= packet->getByteLength();

        return false;
    }
}
