#include "Peripheral.h"
#include "Port.h"
#include "ComputerExceptions.h"

Peripheral::Peripheral():name(""),isConnected(false),port(nullptr){}

Peripheral::Peripheral(const std::string& name):name(name),isConnected(false),port(nullptr){}

bool Peripheral::connectTo(Port* p){
    if(!p){
        throw PeripheralNotRespondingException("port is null");
    }
    port=p;
    isConnected=true;
    return true;
}

void Peripheral::disconnect(){
    port=nullptr;
    isConnected=false;
}