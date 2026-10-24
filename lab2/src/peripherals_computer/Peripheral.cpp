#include "Peripheral.h"
#include "ComputerExceptions.h"
#include "Port.h"

Peripheral::Peripheral():name(""),isConnected(false),port(nullptr){}

Peripheral::Peripheral(const std::string& name):name(name),isConnected(false),port(nullptr){}

bool Peripheral::connectTo(Port* targetPort){
    if(!targetPort){
        throw PeripheralNotRespondingException("port is null");
    }
    port=targetPort;
    isConnected=true;
    return true;
}

void Peripheral::disconnect(){
    port=nullptr;
    isConnected=false;
}
