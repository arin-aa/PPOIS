#include "DiagnosticService.h"
#include "Computer.h"
#include "Logger.h"
#include "Sensor.h"
#include "Storage.h"

const int DIAGNOSTIC_SERVICE_NOT_AVAILABLE=-1;
const char* const MSG_CRITICAL_TEMPERATURE="Critical temperature";
const char* const MSG_STORAGE_FAILED="Storage integrity failed";
const char* const MSG_DIAGNOSTIC_START="Running diagnostic";

DiagnosticService::DiagnosticService():logger(nullptr),issuesFound(0){}

DiagnosticService::DiagnosticService(Logger* logger):logger(logger),issuesFound(0){}

bool DiagnosticService::checkTemperature(Computer* computer,Sensor* sensor){
    if(!computer || !sensor){
        return false;
    }
    if(sensor->isCritical()){
        issuesFound++;
        if(logger){
            logger->log(MSG_CRITICAL_TEMPERATURE);
        }
        return false;
    }
    return true;
}

bool DiagnosticService::checkStorage(Computer* computer,Storage* storage){
    if(!computer || !storage){
        return false;
    }
    if(storage->freeSpace()<0){
        issuesFound++;
        if(logger){
            logger->log(MSG_STORAGE_FAILED);
        }
        return false;
    }
    return true;
}

int DiagnosticService::runFullDiagnostic(Computer* computer){
    if(!computer){
        return DIAGNOSTIC_SERVICE_NOT_AVAILABLE;
    }
    issuesFound=0;
    if(logger){
        logger->log(MSG_DIAGNOSTIC_START);
    }
    for(Storage* storage:computer->storages){
        checkStorage(computer,storage);
    }
    return issuesFound;
}
