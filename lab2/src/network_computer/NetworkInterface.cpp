#include "NetworkInterface.h"
#include "MacAddress.h"
#include "IpAddress.h"
#include "Packet.h"
#include "ComputerExceptions.h"

NetworkInterface::NetworkInterface():name(""),mac(nullptr),ip(nullptr),isUp(false),speedMbps(0){}

NetworkInterface::NetworkInterface(const std::string& name,int speedMbps):name(name),mac(nullptr),ip(nullptr),isUp(false),speedMbps(speedMbps){}

bool NetworkInterface::up(){
    if(isUp){
        return false;
    }
    isUp=true;
    return true;
}

bool NetworkInterface::down(){
    if(!isUp){
        return false;
    }
    isUp=false;
    return true;
}

bool NetworkInterface::send(Packet* packet,IpAddress* target){
    if(!isUp){
        throw NetworkDisconnectedException("interface is down");
    }
    if(!packet || !target){
        return false;
    }
    return packet->decrementTtl()>0;
}

bool NetworkInterface::receive(Packet* packet){
    if(!isUp){
        return false;
    }
    if(!packet){
        return false;
    }
    return packet->isValid();
}