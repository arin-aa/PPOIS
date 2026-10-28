#include "Cooler.h"

const char* const COOLER_MAKER="Cooler Master";
const int COOLER_WATTS=5;

Cooler::Cooler():Component("",COOLER_MAKER,COOLER_WATTS),maxTdpWatts(0){}

Cooler::Cooler(const std::string& name,int maxTdpWatts):Component(name,COOLER_MAKER,COOLER_WATTS),maxTdpWatts(maxTdpWatts){}

int Cooler::headroom(int tdp){
    return maxTdpWatts-tdp;
}
