#pragma once
#include "Computer.h"
#include <vector>

class NetworkInterface;
class Packet;

class Server:public Computer{
private:
    int rackUnits;
    std::string raidLevel;
    long uptimeHours;
    std::vector<NetworkInterface*> nics;

public:
    Server();
    Server(const std::string& hostname,int rackUnits);

    void setupRaid(const std::string& level);
    bool handleRequest(Packet* packet);
    void restart();

    friend class NetworkInterface;
};