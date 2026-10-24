#include "Server.h"
#include "NetworkInterface.h"
#include "Packet.h"

const char* const DEFAULT_RAID_LEVEL="none";
const int DEFAULT_RACK_UNITS=1;

Server::Server():Computer(),rackUnits(DEFAULT_RACK_UNITS),raidLevel(DEFAULT_RAID_LEVEL),uptimeHours(0){}

Server::Server(const std::string& hostname,int rackUnits):Computer(hostname),rackUnits(rackUnits),raidLevel(DEFAULT_RAID_LEVEL),uptimeHours(0){}

void Server::setupRaid(const std::string& level){
    if(level.empty()){
        return;
    }
    raidLevel=level;
}

bool Server::handleRequest(Packet* packet){
    if(!packet){
        return false;
    }
    return packet->isValid();
}

void Server::restart(){
    powerOff();
    powerOn();
    uptimeHours=0;
}
