#include "CompatibilityChecker.h"
#include "Motherboard.h"
#include "CPU.h"
#include "RAM.h"
#include "PSU.h"
#include "Case.h"
#include "Component.h"

CompatibilityChecker::CompatibilityChecker():strictMode(false),checksDone(0){}

CompatibilityChecker::CompatibilityChecker(bool strictMode):strictMode(strictMode),checksDone(0){}

bool CompatibilityChecker::checkSocket(Motherboard* mb,CPU* cpu){
    if(!mb || !cpu){
        return false;
    }
    checksDone++;
    return mb->socket==cpu->socket;
}

int CompatibilityChecker::checkRam(Motherboard* mb,RAM* ram){
    if(!mb || !ram){
        return -1;
    }
    checksDone++;
    if(ram->type=="DDR4"){
        return 0;
    }
    if(ram->type=="DDR5"){
        return 1;
    }
    return -1;
}

int CompatibilityChecker::checkPower(PSU* psu,Component* component){
    if(!psu || !component){
        return -1;
    }
    checksDone++;
    return psu->wattage-component->powerWatts;
}

bool CompatibilityChecker::checkCaseFit(Case* chassis,Component* component){
    if(!chassis || !component){
        return false;
    }
    checksDone++;
    int needed=component->lengthMM+20;
    return needed<=chassis->maxGpuLength;
}

