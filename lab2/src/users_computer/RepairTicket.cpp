#include "RepairTicket.h"
#include "Computer.h"
#include "Technician.h"

const char* const STATUS_OPEN="open";
const char* const STATUS_IN_PROGRESS="in_progress";
const char* const STATUS_CLOSED="closed";
const char* const ESCALATION_MARK=" escalated";

RepairTicket::RepairTicket():id(0),description(""),status(STATUS_OPEN),computer(nullptr),technician(nullptr){}

RepairTicket::RepairTicket(int id,const std::string& description,Computer* computer):id(id),description(description),status(STATUS_OPEN),
    computer(computer),technician(nullptr){}

bool RepairTicket::assign(Technician* assignee){
    if(!assignee){
        return false;
    }
    technician=assignee;
    status=STATUS_IN_PROGRESS;
    return true;
}

bool RepairTicket::close(){
    if(status==STATUS_CLOSED){
        return false;
    }
    status=STATUS_CLOSED;
    return true;
}

bool RepairTicket::escalate(){
    if(status==STATUS_CLOSED){
        return false;
    }
    description+=ESCALATION_MARK;
    return true;
}

std::string RepairTicket::getStatus(){
    return status;
}

std::string RepairTicket::getDescription(){
    return description;
}
