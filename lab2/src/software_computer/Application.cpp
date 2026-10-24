#include "Application.h"
#include "Computer.h"
#include "Motherboard.h"
#include "Storage.h"

const int RAM_PER_SLOT_MB=8192;
const int MB_PER_GB=1024;

Application::Application():Software(),requiredRamMb(0),licenseKey(""){}

Application::Application(const std::string& name,const std::string& version,int sizeMb,int requiredRamMb,const std::string& licenseKey):
    Software(name,version,sizeMb),requiredRamMb(requiredRamMb),licenseKey(licenseKey){}

bool Application::install(Storage* storage){
    if(!storage || !storage->write(sizeMb/MB_PER_GB+1)){
        return false;
    }
    isInstalled=true;
    return true;
}

bool Application::uninstall(Storage* storage){
    if(!storage || !isInstalled){
        return false;
    }
    storage->erase(sizeMb/MB_PER_GB+1);
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
    if(!computer || !computer->motherboard){
        return false;
    }
    Motherboard* board=computer->motherboard;
    int totalRamMb=board->ramSlots*RAM_PER_SLOT_MB;
    return totalRamMb>=requiredRamMb;
}
