#include "OperatingSystem.h"
#include "Application.h"
#include "ComputerExceptions.h"
#include "Driver.h"
#include "Folder.h"
#include "Process.h"
#include "Storage.h"

const char* const OS_NAME="OS";
const char* const OS_DEFAULT_VERSION="1.0";
const int OS_SIZE_MB=5000;
const char* const DEFAULT_ARCHITECTURE="x86_64";
const int FIRST_PID=1000;

OperatingSystem::OperatingSystem():Software(OS_NAME,OS_DEFAULT_VERSION,OS_SIZE_MB),family(""),
    architecture(DEFAULT_ARCHITECTURE),rootFolder(nullptr),isBooted(false),nextPid(FIRST_PID){}

OperatingSystem::OperatingSystem(const std::string& family,const std::string& architecture,const std::string& version):
    Software(OS_NAME,version,OS_SIZE_MB),family(family),architecture(architecture),rootFolder(nullptr),isBooted(false),nextPid(FIRST_PID){}

OperatingSystem::~OperatingSystem()=default;

bool OperatingSystem::install(Storage* storage){
    if(!storage){
        return false;
    }
    isInstalled=true;
    return true;
}

bool OperatingSystem::uninstall(Storage* storage){
    if(!storage){
        return false;
    }
    isInstalled=false;
    isBooted=false;
    return true;
}

bool OperatingSystem::boot(){
    if(!isInstalled){
        throw BootFailureException("OS is not installed");
    }
    if(isBooted){
        return true;
    }
    for(Driver* driver:drivers){
        if(!driver->isSigned){
            throw BootFailureException("unsigned driver cannot be loaded");
        }
        driver->isLoaded=true;
    }
    isBooted=true;
    return true;
}

Process* OperatingSystem::startProcess(Application* app){
    if(!app){
        return nullptr;
    }
    processes.push_back(std::make_unique<Process>(nextPid++,app,app->sizeMb));
    return processes.back().get();
}

bool OperatingSystem::killProcess(int pid){
    for(auto& process:processes){
        if(process->pid==pid){
            process->terminate();
            return true;
        }
    }
    return false;
}

bool OperatingSystem::installDriver(Driver* driver){
    if(!driver || !driver->isSigned){
        return false;
    }
    drivers.push_back(driver);
    return true;
}

Driver* OperatingSystem::findDriverFor(Component* component){
    for(Driver* driver:drivers){
        if(driver->matches(component)){
            return driver;
        }
    }
    throw DriverNotFoundException("no driver installed for the component");
}

bool OperatingSystem::isRunning(){
    return isBooted;
}

int OperatingSystem::getProcessCount(){
    return static_cast<int>(processes.size());
}
