#include "Computer.h"
#include "Motherboard.h"
#include "PSU.h"
#include "Case.h"
#include "Storage.h"
#include "OperatingSystem.h"
#include "User.h"

Computer::Computer():hostname(""),isPoweredOn(false),motherboard(nullptr),psu(nullptr),chassis(nullptr),os(nullptr),owner(nullptr){}

Computer::Computer(const std::string& hostname):hostname(hostname),isPoweredOn(false),motherboard(nullptr),psu(nullptr),chassis(nullptr),os(nullptr),owner(nullptr){}

void Computer::powerOn(){
    if(isPoweredOn){
        return;
    }
    if(os){
        os->boot();
    }
    isPoweredOn=true;
}

void Computer::powerOff(){
    isPoweredOn=false;
}

void Computer::addStorage(Storage* storage){
    if(!storage){
        return;
    }
    storages.push_back(storage);
}

void Computer::installOs(OperatingSystem* newOs){
    if(!newOs){
        return;
    }
    os=newOs;
}

int Computer::totalPowerDraw(){
    int total=0;
    for(Storage* s:storages){
        if(s){
            total+=s->powerWatts;
        }
    }
    return total;
}