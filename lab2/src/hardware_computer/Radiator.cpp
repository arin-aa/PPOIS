#include "Radiator.h"

const char* const RAD_NAME="Radiator";
const int ML_PER_MM=2;

Radiator::Radiator():Cooler(RAD_NAME,0),radiatorLengthMm(0),coolantMl(0){}

Radiator::Radiator(int radiatorLengthMm,int maxTdpWatts):Cooler(RAD_NAME,maxTdpWatts),radiatorLengthMm(radiatorLengthMm),coolantMl(0){}

int Radiator::refill(int milliliters){
    int capacity=radiatorLengthMm*ML_PER_MM;
    coolantMl+=milliliters;
    if(coolantMl>capacity){
        coolantMl=capacity;
    }
    return coolantMl;
}
