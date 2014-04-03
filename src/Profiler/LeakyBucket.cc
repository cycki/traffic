#include "LeakyBucket.h"

Define_Module(LeakyBucket)

void LeakyBucket::initialize(){
	AbstractProfiler::initialize();
	MAKSYMALNE_CIEKNIECIE = par("byteFlow");
	ileMozeWyciec = MAKSYMALNE_CIEKNIECIE;
	lastFlowIncrement = SIMTIME_ZERO;
	lastDelayedPacket = NULL;
}

bool LeakyBucket::acceptPacket(NetPacket* packet, simtime_t& delay){
	simtime_t currentTime = simTime();
	simtime_t timeDiff = currentTime - lastFlowIncrement;

	if(timeDiff > 0)
		ileMozeWyciec = std::min((int32_t)(ileMozeWyciec + MAKSYMALNE_CIEKNIECIE * timeDiff.dbl()), MAKSYMALNE_CIEKNIECIE);
	lastFlowIncrement = currentTime;

	if(packet == lastDelayedPacket)
		return true;
	else if(packet->getByteLength() <= ileMozeWyciec)
	{
		ileMozeWyciec -= packet->getByteLength();
		return true;
	}
	else
	{
		lastDelayedPacket = packet;
		delay = (double)(packet->getByteLength() - ileMozeWyciec) / MAKSYMALNE_CIEKNIECIE;
		ileMozeWyciec -= packet->getByteLength();
		return false;
	}
}
