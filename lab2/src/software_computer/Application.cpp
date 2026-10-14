#include "Application.h"
#include "Computer.h"
#include "Storage.h"
#include "Motherboard.h"

Application::Application():Software(),requiredRamMb(0),licenseKey(""){}

Application::Application(const std::string& name,const std::string& version,int sizeMb,int requiredRamMb,const std::string& licenseKey):Software(name,version,sizeMb),requiredRamMb(requiredRamMb),licenseKey(licenseKey){}

bool Application::install(Storage* storage){
    if(!storage){
        return false;
    }
    isInstalled=true;
    return true;
}

bool Application::uninstall(Storage* storage){
    if(!storage){
        return false;
    }
    isInstalled=false;
    return true;
}

bool Application::checkLicense(const std::string& key){
    if(key.empty() || licenseKey.empty()){
        return false;
    }
    return key==licenseKey;
}

bool Application::canRunOn(Computer* computer){
    if(!computer){
        return false;
    }
    if(!computer->motherboard){
        return false;
    }
    int totalRam=computer->motherboard->ramSlots*8192;
    return totalRam>=requiredRamMb;
}