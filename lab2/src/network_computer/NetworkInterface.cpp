#include "NetworkInterface.h"
#include "ComputerExceptions.h"
#include "IpAddress.h"
#include "MacAddress.h"
#include "Packet.h"

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
    if(!target->isValid()){
        throw InvalidAddressException("target address is malformed");
    }
    return packet->decrementTtl()>0;
}

bool NetworkInterface::receive(Packet* packet){
    if(!isUp || !packet){
        return false;
    }
    return packet->isValid();
}

bool NetworkInterface::isActive(){
    return isUp;
}
