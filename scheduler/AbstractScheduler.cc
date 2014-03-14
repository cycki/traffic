/*
 * AbstractScheduler.cc
 *
 *  Created on: 2011-04-09
 *      Author: Jagger
 */

#include "AbstractScheduler.h"

void AbstractScheduler::initialize()
{
        timeForServingNextPacketEvent = new cMessage("timeForNextPacket");
        numReceived = 0;
        numSent = 0;
}

void AbstractScheduler::finish(){
    recordScalar("#PacketsSent", numSent);
    recordScalar("#PacketsReceived", numReceived);
}

void AbstractScheduler::handleMessage(cMessage* receivedMessage)
{
        simtime_t processDelay = par("processDelay");

        if(receivedMessage != timeForServingNextPacketEvent)//je¿eli komunikat nie pochodzi od nas..
        {

                Message *pck = check_and_cast<Message *>(receivedMessage);//...tzn. ¿e to nasz pakiecik wiêc rzutujemy.
                numReceived++;                                            //zliczamy
                bool queued = receivePacket(pck, pck->getArrivalGateId());//kolejkujemy, przygotowujemy do obs³ugi

                if(queued)
                {
                        // Jesli udalo nam sie zakolejkowac pakiet i nie przetwarzamy w tym
                        // momencie zadnego pakietu, to powinnismy to zrobic teraz.
                        if(!timeForServingNextPacketEvent->isScheduled())
                                scheduleAt(simTime() + processDelay, timeForServingNextPacketEvent);
                }
                else // Pakiet zostal odrzucony
                {
                        EV << "Packet " << pck->getName() << " discarded.\n";
                        delete pck;
                }
        }
        else //wiadomosc pochodzi od nas
        {

                // Wyciagamy pakiet z kolejki zgodnie z zaimplementowanym algorytmem schedulingu:
                Message* pck = getPacketForDeparture();
                //  i wysylamy go dalej.
                send(pck, "out");

                // Robimy staty:
                numSent++;

                // Po wyslaniu pakietu sprawdzamy czy istnieje inny pakiet oczekujacy
                // na wyslanie. Jesli tak, to go przetwarzamy.
                if(hasPacketsAwaitingDeparture()){
                    scheduleAt(simTime() + processDelay, timeForServingNextPacketEvent);
                }
        }
}
