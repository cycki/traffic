#ifndef ONOFFGENERATOR_H_
#define ONOFFGENERATOR_H_

#include "AbstractGenerator.h"

class OnOffGenerator: public AbstractGenerator {
protected:
    double shape;
    double scale;
    double shift;

    virtual void initialize();
    virtual simtime_t getNextPacketCreationTime(
            simtime_t lastPacketCreationTime);
};

#endif /* ONOFFGENERATOR_H_ */
