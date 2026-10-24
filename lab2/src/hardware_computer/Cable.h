#pragma once
#include <string>

class Port;

class Cable{
private:
    std::string type;
    double lengthMeters;

public:
    Cable();
    Cable(const std::string& type,double lengthMeters);

    bool isCompatibleWith(Port* port);
};
