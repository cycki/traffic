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
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <Message_m.h>

#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator : public cSimpleModule{

  public:
    Generator();
    virtual ~Generator();

  protected:
    virtual void initialize();
    virtual Message* generateMessage();
    cMessage *timeoutEvent;
    int sessionDurability;
    long int counter;
    double timeBetweenPackets;
    int packetDurability;
    int priority;
};

#endif /* GENERATOR_H_ */