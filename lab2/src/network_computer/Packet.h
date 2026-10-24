#pragma once

class IpAddress;

class Packet{
public:
    IpAddress* source;
    IpAddress* destination;
    int sizeBytes;
    int ttl;

public:
    Packet();
    Packet(IpAddress* source,IpAddress* destination,int sizeBytes);

    bool isValid();
    int decrementTtl();
    int getTtl();
};
