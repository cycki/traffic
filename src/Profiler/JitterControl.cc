#include "JitterControl.h"

Define_Module(JitterControl)

void JitterControl::initialize()
{
	AbstractProfiler::initialize();
	packetDelaySignal = registerSignal("AveragePacketDelay");
	expectedPacketDelay = par("expectedPacketDelay");
	currentPacketDelay = SIMTIME_ZERO;
	lastPacketSendTime = SIMTIME_ZERO;
	packetDelaySum = SIMTIME_ZERO;
	packetsReceived = 0;
	lastQueuedPacket = NULL;
	WATCH(currentPacketDelay);
}

bool JitterControl::acceptPacket(NetPacket* packet, simtime_t& delay)
{
	if(packet == lastQueuedPacket)
	{
		delay = simTime() - lastPacketSendTime;
		packetDelaySum += delay;
        lastPacketSendTime = simTime();


		currentPacketDelay = packetDelaySum / packetsReceived;
		emit(packetDelaySignal, currentPacketDelay);

		return true;
	}
	else
	{
		packetsReceived++;

		simtime_t diff = simTime() - lastPacketSendTime;

		delay = expectedPacketDelay * packetsReceived - packetDelaySum - diff;
		delay = std::max(delay, SIMTIME_ZERO);

		lastQueuedPacket = packet;
		return false;
	}
}
