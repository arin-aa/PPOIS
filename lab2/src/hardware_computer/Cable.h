#pragma once
#include <string>

class Port;

class Cable{
private:
    std::string type;
    double lengthM;

public:
    Cable();
    Cable(const std::string& type,double lengthM);

    bool isCompatibleWith(Port* port);
};