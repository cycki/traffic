#ifndef POISSONGENERATOR_H_
#define POISSONGENERATOR_H_

#include "AbstractGenerator.h"

class PoissonGenerator: public AbstractGenerator {
protected:

    double poissonLambda;
    virtual void initialize();
    virtual simtime_t getNextPacketCreationTime(
            simtime_t lastPacketCreationTime);
};

#endif /* POISSONGENERATOR_H_ */
