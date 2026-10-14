#pragma once
#include <string>

class IpAddress{
public:
    std::string address;
    int subnetMask;
public:
    IpAddress();
    IpAddress(const std::string& address,int subnetMask);

    bool isValid();
    bool isInSameSubnet(IpAddress* other);
};