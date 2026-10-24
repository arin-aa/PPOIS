#pragma once
#include <string>

class MacAddress;
class IpAddress;
class Packet;
class Server;

class NetworkInterface{
public:
    std::string name;
    MacAddress* mac;
    IpAddress* ip;
    bool isUp;
    int speedMbps;

public:
    NetworkInterface();
    NetworkInterface(const std::string& name,int speedMbps);

    bool up();
    bool down();
    bool send(Packet* packet,IpAddress* target);
    bool receive(Packet* packet);
    bool isActive();

    friend class Server;
};
