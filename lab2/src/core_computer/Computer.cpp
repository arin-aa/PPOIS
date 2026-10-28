#include "Computer.h"
#include "ComputerExceptions.h"
#include "Motherboard.h"
#include "OperatingSystem.h"
#include "PSU.h"
#include "Storage.h"

const int BASE_WATTS=30;
const int LOAD=50;

Computer::Computer():hostname(""),bootCount(0),motherboard(nullptr),psu(nullptr),os(nullptr){}

Computer::Computer(const std::string& hostname):hostname(hostname),bootCount(0),motherboard(nullptr),psu(nullptr),os(nullptr){}

void Computer::assemble(Motherboard* board,PSU* supply){
    motherboard=board;
    psu=supply;
}

void Computer::addStorage(Storage* storage){
    storages.push_back(storage);
}

void Computer::installOs(OperatingSystem* newOs){
    if(storages.empty()){
        throw InvalidConfigurationException(hostname+" has no disk for the OS");
    }
    storages[0]->write(newOs->install(storages[0]->freeSpace()));
    os=newOs;
}

void Computer::powerOn(){
    if(!motherboard || !psu){
        throw BootFailureException(hostname+" is not assembled");
    }
    if(powerReserve()<0){
        throw InsufficientPowerException(hostname+" draws more than the PSU gives");
    }
    if(os){
        os->boot();
    }
    bootCount++;
}

int Computer::freeStorageGb(){
    int freeGb=0;
    for(Storage* storage:storages){
        freeGb+=storage->freeSpace();
    }
    return freeGb;
}

int Computer::powerDraw(){
    int watts=BASE_WATTS;
    if(motherboard){
        watts+=motherboard->draw(LOAD);
    }
    for(Storage* storage:storages){
        watts+=storage->draw(LOAD);
    }
    return watts;
}

int Computer::powerReserve(){
    if(!psu){
        throw BootFailureException(hostname+" has no power supply");
    }
    return psu->reserve(powerDraw());
}
