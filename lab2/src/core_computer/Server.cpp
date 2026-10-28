#include "Server.h"
#include "ComputerExceptions.h"
#include "NetworkInterface.h"
#include "Packet.h"

const char* const RAID0="RAID0";
const char* const RAID1="RAID1";
const char* const RAID5="RAID5";
const int USABLE_0=100;
const int USABLE_1=50;
const int USABLE_5=67;
const int NIC_WATTS=10;
const int RACK_WATTS=15;

Server::Server():Computer(),rackUnits(1),raidLevel(RAID0),requestsServed(0){}

Server::Server(const std::string& hostname,int rackUnits,NetworkInterface* firstNic):Computer(hostname),rackUnits(rackUnits),raidLevel(RAID0),requestsServed(0){
    nics.push_back(firstNic);
}

int Server::configureRaid(const std::string& level){
    if(level!=RAID0 && level!=RAID1 && level!=RAID5){
        throw InvalidConfigurationException("unknown RAID level "+level);
    }
    raidLevel=level;
    return level==RAID0?USABLE_0:(level==RAID1?USABLE_1:USABLE_5);
}

int Server::handleRequest(Packet* packet){
    if(nics.empty()){
        throw NetworkDisconnectedException(hostname+" has no network card");
    }
    requestsServed++;
    return nics[0]->transmitNs(packet->forward());
}

int Server::powerDraw(){
    return Computer::powerDraw()+static_cast<int>(nics.size())*NIC_WATTS+rackUnits*RACK_WATTS;
}
