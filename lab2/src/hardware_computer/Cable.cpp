#include "Cable.h"
#include "ComputerExceptions.h"

const int LOSS_PER_METER=50;

Cable::Cable():type(""),lengthMeters(0.0),maxMbps(0){}

Cable::Cable(const std::string& type,double lengthMeters,int maxMbps):type(type),lengthMeters(lengthMeters),maxMbps(maxMbps){}

void Cable::match(const std::string& portType){
    if(type!=portType){
        throw InvalidConfigurationException(type+" cable does not fit a "+portType+" port");
    }
}

int Cable::effectiveMbps(){
    int speed=maxMbps-static_cast<int>(lengthMeters*LOSS_PER_METER);
    return speed<0?0:speed;
}
