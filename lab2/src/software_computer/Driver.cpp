#include "Driver.h"
#include "Component.h"
#include "Storage.h"

Driver::Driver():Software(),deviceName(""),isSigned(false),isLoaded(false){}

Driver::Driver(const std::string& name,const std::string& deviceName,bool isSigned):Software(name,"1.0",10),deviceName(deviceName),isSigned(isSigned),isLoaded(false){}

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
