#include "Server.h"
#include "NetworkInterface.h"
#include "Packet.h"

Server::Server():Computer(),rackUnits(1),raidLevel("none"),uptimeHours(0){}

Server::Server(const std::string& hostname,int rackUnits):Computer(hostname),rackUnits(rackUnits),raidLevel("none"),uptimeHours(0){}

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
    if(!packet->isValid()){
        return false;
    }
    return true;
}

void Server::restart(){
    powerOff();
    powerOn();
    uptimeHours=0;
}