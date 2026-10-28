#include "Component.h"

const int PCT=100;

Component::Component():name(""),manufacturer(""),powerWatts(0){}

Component::Component(const std::string& name,const std::string& manufacturer,int powerWatts):name(name),manufacturer(manufacturer),
    powerWatts(powerWatts){}

bool Component::isNamed(const std::string& key){
    return key==name || key==manufacturer;
}

int Component::draw(int loadPercent){
    return powerWatts*loadPercent/PCT;
}
