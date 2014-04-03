#include "MMPPGenerator.h"

Define_Module(MMPPGenerator);

void MMPPGenerator::initialize() {
    quantState = par("quantState");
    maxPack = par("maxPack");
    trans = new double[quantState][3];
    poissonLambda = new double[quantState];
    srand(time(NULL));
    string transP = par("transP");
    string poissonLambdaP = par("poissonLambdaP");

    stringstream par2array(stringstream::in | stringstream::out);

    if (transP.length() == 0) {
        for (int i = 0; i < quantState; i++) {
            trans[i][0] = 1 - ((double) (rand() % 100)) / 100;
            trans[i][1] = 1 - ((double) (rand() % 100)) / 100;
            if (trans[i][1] > 1 - trans[i][0])
                trans[i][1] -= trans[i][0];

            trans[i][2] = 1 - trans[i][0] - trans[i][1];
        }
    } else {
        par2array.str("");
        par2array << transP;

        for (int i = 0; i < quantState; i++) {
            for (int j = 0; j < 3; j++) {
                trans[i][j] = -1;
                par2array >> trans[i][j];
                if (trans[i][j] < 0 || trans[i][j] > 1) {
                    EV
                              << "Blad parametrow: za malo danych do wypelnienia tablicy przejsc pomiedzy stanami lub parametry z poza zakresu\n";
                }
            }
            if (trans[i][0] + trans[i][1] + trans[i][2] != 1) {
                EV
                          << "Blad parametrow: niepoprawne parametry przejsc pomiedzy stanami\n";
            }
        }
    }

    if (poissonLambdaP.length() == 0) {
        // srand(time(NULL));

        for (int i = 0; i < quantState; i++) {
            bool isGood;

            do {
                isGood = true;
                poissonLambda[i] = rand() % (200 * quantState) + 1;
                for (int j = 0; j < i; j++) {
                    if ((poissonLambda[i] / poissonLambda[j] < 2)
                            && (poissonLambda[i] / poissonLambda[j] > 0.5)) {
                        isGood = false;
                        EV << poissonLambda[i] << " " << poissonLambda[j]
                                  << "\n";
                        break;
                    }
                }
            } while (!isGood);

            EV << "lamdba_" << i << " = " << poissonLambda[i] << endl;
        }
    } else {
        par2array.str("");
        par2array << poissonLambdaP;

        for (int i = 0; i < quantState; i++) {
            poissonLambda[i] = -1;
            par2array >> poissonLambda[i];
            if (poissonLambda[i] < 0) {
                EV
                          << "Blad parametrow: za malo parametrow rozkladow prawdopodobienstwa lub parametry niepoprawne\n";
            }
        }
    }

    pack = 0;
    state = 0;
    addedTime = 0;

    AbstractGenerator::initialize();
}

simtime_t MMPPGenerator::getNextPacketCreationTime(
        simtime_t lastPacketCreationTime) {
    if (pack >= maxPack) {
        double whereNextP = (double) (1 - ((double) (rand() % 100)) / 100);
        EV << "whereNextP = " << whereNextP << "\n";
        for (int i = 0; i < 3; i++) {
            double P = 0;
            for (int j = 0; j <= i; j++) {
                P += trans[state][j];
            }
               if (whereNextP <= P) {
                switch (i) {
                case 0:
                    state = (state == 0) ? (quantState - 1) : (state - 1);
                    break;
                case 1:
                    state = i;
                    break;
                case 2:
                    state = (state == (quantState - 1)) ? 0 : (state + 1);
                    break;
                default:
                    break;

                }
                EV << "state = " << state << "\n";
                break;
            }

        }
        pack = 0;
    }
    pack++;

    addedTime = poisson(poissonLambda[state], 0.2);
    return lastPacketCreationTime + addedTime;
}
