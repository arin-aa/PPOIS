#include "Port.h"
#include "Cable.h"
#include "ComputerExceptions.h"
#include "Peripheral.h"

Port::Port():type(""),cable(nullptr){}

Port::Port(const std::string& type):type(type),cable(nullptr){}

void Port::plug(Cable* newCable){
    if(!newCable){
        return;
    }
    if(!newCable->isCompatibleWith(this)){
        throw InvalidConfigurationException("cable does not match port type");
    }
    cable=newCable;
}

void Port::unplug(){
    cable=nullptr;
}

bool Port::connectPeripheral(Peripheral* peripheral){
    if(!peripheral || !cable){
        return false;
    }
    return peripheral->isConnected;
}
