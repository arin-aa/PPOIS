#include "Radiator.h"

Radiator::Radiator():Cooler("Radiator",250,30),lengthMm(0),coolantLevel(100){}

Radiator::Radiator(int lengthMm):Cooler("Radiator",250,30),lengthMm(lengthMm),coolantLevel(100){}

std::string Radiator::describe(){
    return "Radiator "+std::to_string(lengthMm)+"mm";
}

bool Radiator::refillCoolant(int ml){
    if(ml<=0){
        return false;
    }
    coolantLevel+=ml;
    if(coolantLevel>100){
        coolantLevel=100;
    }
    return true;
}