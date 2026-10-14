#include "Component.h"

Component::Component():name(""),manufacturer(""),powerWatts(0),lengthMM(0){}

Component::Component(const std::string& name,const std::string& manufacturer,int powerWatts,int lengthMM):name(name),manufacturer(manufacturer),powerWatts(powerWatts),lengthMM(lengthMM){}