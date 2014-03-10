//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <Generator.h>

Generator::Generator()
{
    timeoutEvent = NULL;
}

Generator::~Generator()
{
    cancelAndDelete(timeoutEvent);
}

void Generator::initialize()
{
    timeoutEvent = new cMessage("timeoutEvent");
    sessionDurability = par("sessionDurability");
    packetDurability = par("packetDurability");
    timeBetweenPackets = par("timeBetweenPackets");
    priority = par("priority");
    counter = 0;

    // Generate and send initial message.
    EV << "Sending initial message\n";
    cMessage *msg = new cMessage("initialMsg");
    send(msg, "out");
    scheduleAt(simTime(), timeoutEvent);
}



Message *Generator::generateMessage()
{
    // Produce source and destination addresses.
    int src = getIndex();
    int dest = intuniform(0,3);
    if (dest>=src) dest++;

    char msgname[20];
    sprintf(msgname, "tic-%d-to-%d", src, dest);

    Message *msg = new Message(msgname);
    long packetId = counter++/packetDurability;
    msg->setSrc(src);
    msg->setDst(dest);
    msg->setSessionId(1);
    msg->setPacketId(packetId);
    msg->setPriority(priority);
    msg->setPayload(1246789);

    return msg;
}
