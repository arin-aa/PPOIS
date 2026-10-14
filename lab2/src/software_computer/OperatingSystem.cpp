#include "OperatingSystem.h"
#include "Driver.h"
#include "Application.h"
#include "Process.h"
#include "Folder.h"
#include "Storage.h"
#include "ComputerExceptions.h"

OperatingSystem::OperatingSystem():Software("OS","1.0",5000),family(""),architecture("x86_64"),rootFolder(nullptr),isBooted(false){}

OperatingSystem::OperatingSystem(const std::string& family,const std::string& architecture,const std::string& version):Software("OS",version,5000),family(family),architecture(architecture),rootFolder(nullptr),isBooted(false){}

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
    for(Driver* d:drivers){
        if(!d && !d->isSigned){
            throw BootFailureException("unsigned driver cannot be loaded");
        }
        d->isLoaded=true;
    }
    isBooted=true;
    return true;
}

Process* OperatingSystem::startProcess(Application* app){
    if(!app){
        return nullptr;
    }
    static int nextPid=1000;
    Process* p=new Process(nextPid++,app,app->sizeMb);
    processes.push_back(p);
    return p;
}

bool OperatingSystem::killProcess(int pid){
    for(Process* p:processes){
        if(p && p->pid==pid){
            p->terminate();
            return true;
        }
    }
    return false;
}

bool OperatingSystem::installDriver(Driver* driver){
    if(!driver){
        return false;
    }
    if(!driver->isSigned){
        return false;
    }
    drivers.push_back(driver);
    return true;
}

