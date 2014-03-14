#include <omnetpp.h>
#include "Message_m.h"

#ifndef ABSTRACTSCHEDULER_H
#define ABSTRACTSCHEDULER_H

/**
 * Klasa abstrakcyjna definiujaca sposob dzialania typowego schedulera
 * sieciowego. Algorytm schedulingu musi zostac zaimplementowany w metodzie
 * 'getPacketForDeparture'.
 */
class AbstractScheduler : public cSimpleModule
{

    protected:
        cMessage* timeForServingNextPacketEvent;
        long numSent;
        long numReceived;
        /**
         * Iniciuje parametr 'processEvent'.
         */
        virtual void initialize();
        virtual void finish();
        /**
         * Zajmuje sie obsluga zdarzenia wewnetrznego lub komunikatow przychodzacych
         * z zewnatrz.
         */
        virtual void handleMessage(cMessage* msg);

        /**
         * Umieszcza dany pakiet w kolejce pakietow oczekujacych na wyslanie.
         * Numer bramy z ktorej pakiet dotarl moze (ale nie musi) byc wykorzystany
         * przy przydzielaniu pakietu do odpowiedniej kolejki.
         *
         * @return Informuje czy pakiet zostal faktycznie zakolejkowany (true) lub
         * odrzucony np. ze wzgledu na przekroczenie maksymalnej dlugosci kolejki
         * (false).
         */
        virtual bool receivePacket(Message* packet, int gateNum) = 0;

        /**
         * Informuje czy scheduler posiada co najmniej jeden pakiet oczekujacy na
         * wyslanie.
         */
        virtual bool hasPacketsAwaitingDeparture() = 0;
        /**
         * Zwraca kolejny pakiet gotowy do opuszczenia schedulera. Zwrocony pakiet
         * musi byc wewnetrznie usuniety z kolejki pakietow oczekujacych na wyslanie.
         */
        virtual Message* getPacketForDeparture() = 0;
};

#endif /* ABSTRACTSCHEDULER_H */
