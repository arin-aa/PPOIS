#include "CompatibilityChecker.h"
#include "Case.h"
#include "Component.h"
#include "ComputerExceptions.h"
#include "CPU.h"
#include "Motherboard.h"
#include "PSU.h"
#include "RAM.h"

const int COMPATIBILITY_CHECKER_NOT_AVAILABLE=-1;
const char* const DDR4="DDR4";
const char* const DDR5="DDR5";
const int DDR4_INDEX=0;
const int DDR5_INDEX=1;
const int GPU_CLEARANCE_MM=20;

CompatibilityChecker::CompatibilityChecker():strictMode(false),checksDone(0){}

CompatibilityChecker::CompatibilityChecker(bool strictMode):strictMode(strictMode),checksDone(0){}

bool CompatibilityChecker::checkSocket(Motherboard* board,CPU* cpu){
    if(!board || !cpu){
        return false;
    }
    checksDone++;
    return board->socket==cpu->socket;
}

int CompatibilityChecker::checkRam(Motherboard* board,RAM* ram){
    if(!board || !ram){
        return COMPATIBILITY_CHECKER_NOT_AVAILABLE;
    }
    checksDone++;
    if(ram->type==DDR4){
        return DDR4_INDEX;
    }
    if(ram->type==DDR5){
        return DDR5_INDEX;
    }
    return COMPATIBILITY_CHECKER_NOT_AVAILABLE;
}

int CompatibilityChecker::checkPower(PSU* psu,Component* component){
    if(!psu || !component){
        return COMPATIBILITY_CHECKER_NOT_AVAILABLE;
    }
    checksDone++;
    int reserveWatts=psu->wattage-component->powerWatts;
    if(strictMode && reserveWatts<0){
        throw InsufficientPowerException("component exceeds PSU wattage");
    }
    return reserveWatts;
}

bool CompatibilityChecker::checkCaseFit(Case* chassis,Component* component){
    if(!chassis || !component){
        return false;
    }
    checksDone++;
    int requiredLengthMm=component->lengthMm+GPU_CLEARANCE_MM;
    return requiredLengthMm<=chassis->maxGpuLengthMm;
}
