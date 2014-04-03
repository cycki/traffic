#ifndef MMPPGENERATOR_H_
#define MMPPGENERATOR_H_

#include "AbstractGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>

using namespace std;

class MMPPGenerator : public AbstractGenerator
{
protected:
    int quantState; // max 2
    int state;
    double (*trans)[3];
    double *poissonLambda;
    int maxPack;
    int pack;
    double addedTime;


    virtual void initialize();
    virtual simtime_t getNextPacketCreationTime(simtime_t lastPacketCreationTime);

    ~MMPPGenerator() {
        delete [] trans;
        delete [] poissonLambda;
    }
};

#endif /* MMPPGENERATOR_H_ */
