#include "Software.h"

Software::Software():name(""),version(""),sizeMb(0),isInstalled(false){}

Software::Software(const std::string& name,const std::string& version,int sizeMb):name(name),version(version),sizeMb(sizeMb),isInstalled(false){}

bool Software::isInstalledOnDisk(){
    return isInstalled;
}
