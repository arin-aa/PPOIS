#include "Cooler.h"

const char* const COOLER_MANUFACTURER="Generic";
const int COOLER_POWER_WATTS=3;
const int COOLER_LENGTH_MM=80;

Cooler::Cooler():Component("","",COOLER_POWER_WATTS,COOLER_LENGTH_MM),maxTdpWatts(0),noiseDb(0){}

Cooler::Cooler(const std::string& name,int maxTdpWatts,int noiseDb):Component(name,COOLER_MANUFACTURER,COOLER_POWER_WATTS,COOLER_LENGTH_MM),
    maxTdpWatts(maxTdpWatts),noiseDb(noiseDb){}

bool Cooler::canCool(int tdp){
    return maxTdpWatts>=tdp;
}
