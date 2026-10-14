#include "DiagnosticService.h"
#include "Logger.h"
#include "Computer.h"
#include "Storage.h"
#include "Sensor.h"

DiagnosticService::DiagnosticService():logger(nullptr),issuesFound(0){}

DiagnosticService::DiagnosticService(Logger* logger):logger(logger),issuesFound(0){}

bool DiagnosticService::checkTemperature(Computer* computer,Sensor* sensor){
    if(!computer || !sensor){
        return false;
    }
    if(sensor->isCritical()){
        issuesFound++;
        if(logger){
            logger->log("Critical temperature");
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
            logger->log("Storage integrity failed");
        }
        return false;
    }
    return true;
}

int DiagnosticService::runFullDiagnostic(Computer* computer){
    if(!computer){
        return -1;
    }
    issuesFound=0;
    if(logger){
        logger->log("Running diagnostic");
    }
    return issuesFound;
}