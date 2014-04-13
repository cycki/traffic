#include "LeakyBucket.h"

Define_Module(LeakyBucket)

void LeakyBucket::initialize() {
	AbstractProfiler::initialize();
	BUCKET_CAPACITY = par("byteFlow");
	currentMaxLeak = BUCKET_CAPACITY;
	lastFlowIncrement = SIMTIME_ZERO;
	lastDelayedPacket = NULL;
}

bool LeakyBucket::acceptPacket(NetPacket* packet, simtime_t& delay) {
	simtime_t currentTime = simTime();
	simtime_t timeDiff = currentTime - lastFlowIncrement;

	if(timeDiff > 0)
		currentMaxLeak = std::min((int32_t)(currentMaxLeak + BUCKET_CAPACITY * timeDiff.dbl()), BUCKET_CAPACITY);
	lastFlowIncrement = currentTime;

	// Jeśli jest to już opóźniony pakiet
	if(packet == lastDelayedPacket) {
		return true;
	}
	// Jeśli pakiet 'mieści się' w wiadrze wtedy może wyciec
	else if(packet->getByteLength() <= currentMaxLeak) {
		currentMaxLeak -= packet->getByteLength();
		return true;
	}
	// W przeciwnym przypadku pakiet będzie opóźniony
	else {
		lastDelayedPacket = packet;
		delay = (double)(packet->getByteLength() - currentMaxLeak) / BUCKET_CAPACITY;
		currentMaxLeak -= packet->getByteLength();
		return false;
	}
}
