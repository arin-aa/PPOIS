#include "Application.h"
#include "ComputerExceptions.h"

Application::Application():Software(),requiredRamMb(0),licenseKey(""),launches(0){}

Application::Application(const std::string& name,int sizeMb,int requiredRamMb,const std::string& licenseKey):Software(name,sizeMb),
    requiredRamMb(requiredRamMb),licenseKey(licenseKey),launches(0){}

bool Application::checkLicense(const std::string& key){
    return !licenseKey.empty() && key==licenseKey;
}

int Application::launch(int freeRamMb){
    if(!isInstalled){
        throw InvalidConfigurationException(name+" is not installed");
    }
    if(freeRamMb<requiredRamMb){
        throw MemoryOverflowException(name+" needs more memory");
    }
    launches++;
    return freeRamMb-requiredRamMb;
}
