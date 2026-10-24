#include "Component.h"

Component::Component():name(""),manufacturer(""),powerWatts(0),lengthMm(0){}

Component::Component(const std::string& name,const std::string& manufacturer,int powerWatts,int lengthMm):name(name),manufacturer(manufacturer),
    powerWatts(powerWatts),lengthMm(lengthMm){}
