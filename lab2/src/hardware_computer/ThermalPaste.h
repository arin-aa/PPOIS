#pragma once
#include <string>

class ThermalPaste{
private:
    std::string type;
    int ageMonths;
    double conductivity;

public:
    ThermalPaste();
    ThermalPaste(const std::string& type,double conductivity);

    bool isDried();
};
