#include "Port.h"
#include "Cable.h"
#include "Peripheral.h"

Port::Port():type(""),cable(nullptr){}

Port::Port(const std::string& type):type(type),cable(nullptr){}

void Port::plug(Cable* c){
    if(!c){
        return;
    }
    cable=c;
}

void Port::unplug(){
    cable=nullptr;
}

bool Port::connectPeripheral(Peripheral* p){
    if(!p){
        return false;
    }
    if(!p->isConnected){
        return false;
    }
    return true;
}