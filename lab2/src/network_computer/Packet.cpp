#include "Packet.h"
#include "ComputerExceptions.h"
#include "IpAddress.h"

const int BITS_IN_BYTE=8;

Packet::Packet():source(nullptr),destination(""),sizeBytes(0),ttl(0){}

Packet::Packet(IpAddress* source,const std::string& destination,int sizeBytes,int ttl):source(source),destination(destination),
    sizeBytes(sizeBytes),ttl(ttl){}

int Packet::forward(){
    if(ttl<=0){
        throw NetworkDisconnectedException("packet to "+destination+" expired");
    }
    ttl--;
    return sizeBytes*BITS_IN_BYTE;
}

bool Packet::isLocal(){
    return source->sameSubnet(destination);
}
