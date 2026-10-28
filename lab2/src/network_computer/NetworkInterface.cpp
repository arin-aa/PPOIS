#include "NetworkInterface.h"
#include "ComputerExceptions.h"
#include "IpAddress.h"

const int BITS_IN_BYTE=8;
const int NS_PER_US=1000;

NetworkInterface::NetworkInterface():isUp(false),speedMbps(1),bytesSent(0),ip(nullptr){}

NetworkInterface::NetworkInterface(int speedMbps):isUp(false),speedMbps(speedMbps>0?speedMbps:1),bytesSent(0),ip(nullptr){}

void NetworkInterface::connect(IpAddress* newIp){
    newIp->validate();
    ip=newIp;
    isUp=true;
}

int NetworkInterface::transmitNs(int bits){
    if(!isUp || !ip){
        throw NetworkDisconnectedException("interface is down or has no address");
    }
    bytesSent+=bits/BITS_IN_BYTE;
    return bits*NS_PER_US/speedMbps;
}
