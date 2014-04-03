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

#ifndef EXPONENTIALGENERATOR_H_
#define EXPONENTIALGENERATOR_H_

#include "AbstractGenerator.h"

class ExponentialGenerator : public AbstractGenerator
{
protected:
    simtime_t exponentialMean;
    virtual void initialize();
    virtual simtime_t getNextPacketCreationTime(simtime_t lastPacketCreationTime);
};

#endif /* EXPONENTIALGENERATOR_H_ */
