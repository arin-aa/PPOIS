#include "CompatibilityChecker.h"
#include "ComputerExceptions.h"

CompatibilityChecker::CompatibilityChecker():strictMode(false),checksDone(0),minReserveWatts(0){}

CompatibilityChecker::CompatibilityChecker(bool strictMode,int minReserveWatts):strictMode(strictMode),checksDone(0),
    minReserveWatts(minReserveWatts){}

int CompatibilityChecker::checkPower(int supplyWatts,int demandWatts){
    checksDone++;
    int reserve=supplyWatts-demandWatts;
    if(strictMode && reserve<minReserveWatts){
        throw InsufficientPowerException("power reserve is below the required minimum");
    }
    return reserve;
}
