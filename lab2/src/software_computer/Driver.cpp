#include "Driver.h"
#include "Component.h"
#include "ComputerExceptions.h"

const int DRIVER_SIZE_MB=20;

Driver::Driver():Software(),deviceName(""),isSigned(false),bindCount(0){}

Driver::Driver(const std::string& name,const std::string& deviceName,bool isSigned):Software(name,DRIVER_SIZE_MB),deviceName(deviceName),
    isSigned(isSigned),bindCount(0){}

void Driver::bind(Component* part){
    if(!part->isNamed(deviceName)){
        throw DriverNotFoundException(name+" is a driver for "+deviceName+" only");
    }
    bindCount++;
}

void Driver::load(){
    if(!isSigned){
        throw BootFailureException("unsigned driver "+name+" cannot be loaded");
    }
}
