#include "PowerConnector.h"
#include "ComputerExceptions.h"

PowerConnector::PowerConnector():pinCount(0),isPlugged(false){}

PowerConnector::PowerConnector(int pinCount):pinCount(pinCount),isPlugged(false){}

int PowerConnector::attach(){
    if(isPlugged){
        throw InvalidConfigurationException("connector is already plugged");
    }
    isPlugged=true;
    return pinCount;
}
