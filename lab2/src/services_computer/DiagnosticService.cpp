#include "DiagnosticService.h"
#include "Computer.h"
#include "Logger.h"

const int FULL_HEALTH=100;
const int ISSUE_PENALTY=25;

DiagnosticService::DiagnosticService():issuesFound(0),lowReserveWatts(0),lowDiskGb(0),logger(nullptr){}

DiagnosticService::DiagnosticService(int lowReserveWatts,int lowDiskGb,Logger* logger):issuesFound(0),lowReserveWatts(lowReserveWatts),
    lowDiskGb(lowDiskGb),logger(logger){}

int DiagnosticService::scan(Computer* computer){
    if(computer->powerReserve()<lowReserveWatts){
        issuesFound++;
        logger->log("low power reserve");
    }
    if(computer->freeStorageGb()<lowDiskGb){
        issuesFound++;
        logger->log("low disk space");
    }
    return issuesFound;
}

int DiagnosticService::healthScore(){
    int score=FULL_HEALTH-issuesFound*ISSUE_PENALTY;
    return score<0?0:score;
}
