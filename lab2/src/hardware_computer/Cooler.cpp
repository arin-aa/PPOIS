#include "Cooler.h"

Cooler::Cooler():Component("","",3,80),maxTdpWatts(0),noiseDb(0){}

Cooler::Cooler(const std::string& name,int maxTdpWatts,int noiseDb):Component(name,"Generic",3,80),maxTdpWatts(maxTdpWatts),noiseDb(noiseDb){}

bool Cooler::canCool(int tdp){
    return maxTdpWatts>=tdp;
}