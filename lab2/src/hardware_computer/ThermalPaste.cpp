#include "ThermalPaste.h"

const int DRIED_AGE_MONTHS=24;

ThermalPaste::ThermalPaste():type(""),ageMonths(0),conductivity(0.0){}

ThermalPaste::ThermalPaste(const std::string& type,double conductivity):type(type),ageMonths(0),conductivity(conductivity){}

bool ThermalPaste::isDried(){
    return ageMonths>=DRIED_AGE_MONTHS;
}
