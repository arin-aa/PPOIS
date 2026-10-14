#include "PowerConnector.h"

PowerConnector::PowerConnector():pinCount(0),isConnected(false){}

PowerConnector::PowerConnector(int pinCount):pinCount(pinCount),isConnected(false){}

bool PowerConnector::connect(){
    if(isConnected){
        return false;
    }
    isConnected=true;
    return true;
}