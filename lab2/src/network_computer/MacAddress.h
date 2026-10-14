#pragma once
#include <string>

class MacAddress{
public:
    std::string value;
    std::string vendor;

public:
    MacAddress();
    MacAddress(const std::string& value,const std::string& vendor);

    bool isValid();
};