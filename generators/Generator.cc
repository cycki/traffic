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
    timeBetweenPackets = par("timeBetweenPackets");
    priority = par("priority");
    MTU = par("MTU");
    counter = 0;
    scheduleAt(simTime(), timeoutEvent);
}



Message *Generator::generateMessage()
{
    // Produce source and destination addresses.
    int src = getIndex();
    int dest = intuniform(0,3);
    if (dest>=src) dest++;

    char msgname[20];
    long sessionId = counter++/sessionDurability;
    sprintf(msgname, "tic-%d-to-%d, packetId = %ld", src, dest, sessionId);

    Message *msg = new Message(msgname);
    msg->setSrc(src);
    msg->setDst(dest);
    msg->setSessionId(sessionId);
    msg->setPacketId(counter);
    msg->setPriority(priority);
    msg->setPayload("123");

    return msg;
}
