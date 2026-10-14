#include "Case.h"
#include "Motherboard.h"
#include "Fan.h"

Case::Case():Component("Case","NZXT",10,450),formFactor(""),maxGpuLength(0){}

Case::Case(const std::string& formFactor,int maxGpuLength):Component("Case","NZXT",10,450),formFactor(formFactor),maxGpuLength(maxGpuLength){}

std::string Case::describe(){
    return "Case "+formFactor;
}

bool Case::fits(Motherboard* mb){
    if(!mb){
        return false;
    }
    if(mb->formFactor=="ATX" && formFactor=="ATX"){
        return true;
    }
    if(mb->formFactor=="mATX" && (formFactor=="ATX" || formFactor=="mATX")){
        return true;
    }
    return false;
}

bool Case::addFan(Fan* fan){
    if(!fan){
        return false;
    }
    if(fans.size()>=6){
        return false;
    }
    fans.push_back(fan);
    return true;
}