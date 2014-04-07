#include "PriorityAdmissionControl.h"

Define_Module(PriorityAdmissionControl)

/*
Kontrolujemy przyj�cia pakiet�w na podstawie ich priorytet�w
Pakiet wchodzi
Jesli jest mniejszy niz maksymalny przez nas obslugiwany to przechodzi dalej
Nastepnie sprawdzamy czy pakiet nie jest czasami mniejszy od naszego minimalnego priorytetu
Jezeli spelnil oba warunki przechodzi AC jesli nie to trafia w nicosc.
*/


void PriorityAdmissionControl::initialize(){

    //Inicjalizuj�my abstrakcyjne AC
    AbstractAdmissionControl::initialize();
    max = par ("Maximal_priority");
    min = par ("Minimal_priority");

}

bool PriorityAdmissionControl::acceptMsg(NetPacket *msg){
    uint32_t currentPrior = msg->getPriority();
    uint32_t mx = this->max;
    uint32_t mn = this->min;
    if (currentPrior<=mx) {//gorna granica
        if (currentPrior>=mn) {//dolna granica

                return currentPrior;
                   }
            }


}
