#include "Peripheral.h"
#include "ComputerExceptions.h"
#include "Port.h"

const int LATENCY_BASE=100;
const int LATENCY_SCALE=100000;

Peripheral::Peripheral():name(""),isConnected(false),port(nullptr){}

Peripheral::Peripheral(const std::string& name):name(name),isConnected(false),port(nullptr){}

void Peripheral::connectTo(Port* targetPort){
    targetPort->throughput();
    port=targetPort;
    isConnected=true;
}

int Peripheral::ping(){
    if(!isConnected){
        throw PeripheralNotRespondingException(name+" is not connected");
    }
    int speed=port->throughput();
    if(speed<=0){
        throw PeripheralNotRespondingException(name+" has a dead link");
    }
    return LATENCY_BASE+LATENCY_SCALE/speed;
}
