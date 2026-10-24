#include "Driver.h"
#include "Component.h"
#include "Storage.h"

const char* const DRIVER_DEFAULT_VERSION="1.0";
const int DRIVER_SIZE_MB=10;

Driver::Driver():Software(),deviceName(""),isSigned(false),isLoaded(false){}

Driver::Driver(const std::string& name,const std::string& deviceName,bool isSigned):Software(name,DRIVER_DEFAULT_VERSION,DRIVER_SIZE_MB),
    deviceName(deviceName),isSigned(isSigned),isLoaded(false){}

bool Driver::install(Storage* storage){
    if(!storage){
        return false;
    }
    isInstalled=true;
    return true;
}

bool Driver::uninstall(Storage* storage){
    if(!storage){
        return false;
    }
    isInstalled=false;
    isLoaded=false;
    return true;
}

bool Driver::matches(Component* component){
    if(!component){
        return false;
    }
    return component->name==deviceName;
}
