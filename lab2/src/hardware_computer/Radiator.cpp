#include "Radiator.h"

const char* const RADIATOR_NAME="Radiator";
const int MAX_TDP_WATTS=250;
const int NOISE_DB=30;
const int FULL_COOLANT_LEVEL=100;

Radiator::Radiator():Cooler(RADIATOR_NAME,MAX_TDP_WATTS,NOISE_DB),radiatorLengthMm(0),coolantLevel(FULL_COOLANT_LEVEL){}

Radiator::Radiator(int radiatorLengthMm):Cooler(RADIATOR_NAME,MAX_TDP_WATTS,NOISE_DB),radiatorLengthMm(radiatorLengthMm),
    coolantLevel(FULL_COOLANT_LEVEL){}

std::string Radiator::describe(){
    return "Radiator "+std::to_string(radiatorLengthMm)+"mm";
}

bool Radiator::refillCoolant(int milliliters){
    if(milliliters<=0){
        return false;
    }
    coolantLevel+=milliliters;
    if(coolantLevel>FULL_COOLANT_LEVEL){
        coolantLevel=FULL_COOLANT_LEVEL;
    }
    return true;
}

int Radiator::getCoolantLevel(){
    return coolantLevel;
}
