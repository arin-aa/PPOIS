#include "Software.h"
#include "ComputerExceptions.h"

const int MB_PER_GB=1024;

Software::Software():name(""),sizeMb(0),isInstalled(false){}

Software::Software(const std::string& name,int sizeMb):name(name),sizeMb(sizeMb),isInstalled(false){}

int Software::install(int freeGb){
    int needGb=sizeMb/MB_PER_GB+1;
    if(needGb>freeGb){
        throw DiskFullException("no room to install "+name);
    }
    isInstalled=true;
    return needGb;
}
