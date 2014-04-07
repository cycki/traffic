#include "SourceAdmissionControl.h"
#include <vector>
Define_Module(SourceAdmissionControl)

/*
 Kontrolujemy przyjêcia pakietów na podstawie ich Ÿród³a
 Pakiet wchodzi
 Sprawdzamy czy nie nalezy do blokowanych
 jesli nie to przechodzi.
 */

void SourceAdmissionControl::initialize() {

    //Inicjalizujêmy abstrakcyjne AC
    AbstractAdmissionControl::initialize();
    const char* ids = par("BlockedSources");
    //Inicjalizajla listy blokowanych Ÿróde³
    std::vector<int> vIds = cStringTokenizer(ids).asIntVector();

    for (uint32_t i = 0; i < vIds.size(); i++)
        BlockedSources.insert(vIds[i]);

}

bool SourceAdmissionControl::acceptMsg(NetPacket *msg) {
    uint32_t currentSrc = msg->getSrc();
    if (BlockedSources.find(currentSrc) == BlockedSources.end()) {
        return true;
    } else {
        return false;
    }
}

