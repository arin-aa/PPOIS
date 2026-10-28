#include "OperatingSystem.h"
#include "ComputerExceptions.h"
#include "Driver.h"

const int FIRST_PID=1000;

OperatingSystem::OperatingSystem():Software(),isBooted(false),nextPid(FIRST_PID){}

OperatingSystem::OperatingSystem(const std::string& name,int sizeMb):Software(name,sizeMb),isBooted(false),nextPid(FIRST_PID){}

void OperatingSystem::boot(){
    if(!isInstalled){
        throw BootFailureException(name+" is not installed");
    }
    for(Driver* driver:drivers){
        driver->load();
    }
    isBooted=true;
}

void OperatingSystem::addDriver(Driver* driver){
    drivers.push_back(driver);
}

int OperatingSystem::startProcess(Process* process,int freeRamMb){
    if(!isBooted){
        throw BootFailureException(name+" is not running");
    }
    process->start(freeRamMb);
    processes.push_back(*process);
    return nextPid++;
}

int OperatingSystem::killProcess(int pid){
    int index=pid-FIRST_PID;
    if(index<0 || index>=static_cast<int>(processes.size())){
        return -1;
    }
    return processes[index].terminate();
}
