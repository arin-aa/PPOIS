#include "Port.h"
#include "Cable.h"
#include "ComputerExceptions.h"

Port::Port():type(""),speedMbps(0),cable(nullptr){}

Port::Port(const std::string& type,int speedMbps):type(type),speedMbps(speedMbps),cable(nullptr){}

void Port::plug(Cable* newCable){
    newCable->match(type);
    cable=newCable;
}

int Port::throughput(){
    if(!cable){
        throw PeripheralNotRespondingException(type+" port has no cable");
    }
    int linkMbps=cable->effectiveMbps();
    return linkMbps<speedMbps?linkMbps:speedMbps;
}
