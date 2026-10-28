#include "RepairTicket.h"
#include "Computer.h"
#include "ComputerExceptions.h"
#include "Technician.h"

const char* const OPEN="open";
const char* const ASSIGNED="assigned";
const char* const CLOSED="closed";

RepairTicket::RepairTicket():description(""),status(OPEN),hoursSpent(0),computer(nullptr),technician(nullptr){}

RepairTicket::RepairTicket(const std::string& description,Computer* computer):description(description),status(OPEN),hoursSpent(0),computer(computer),technician(nullptr){}

void RepairTicket::assign(Technician* worker){
    if(status!=OPEN){
        throw InvalidConfigurationException("ticket '"+description+"' is already "+status);
    }
    technician=worker;
    status=ASSIGNED;
}

int RepairTicket::diagnose(){
    return computer->powerReserve();
}

int RepairTicket::close(int hours){
    if(status == CLOSED) { 
        throw UnauthorizedAccessException("ticket is already closed");
    }

    if(!technician){
        throw UnauthorizedAccessException("nobody is assigned to '"+description+"'");
    }
    hoursSpent+=hours;
    status=CLOSED;
    return technician->estimate(hoursSpent);
}
