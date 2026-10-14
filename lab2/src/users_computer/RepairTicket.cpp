#include "RepairTicket.h"
#include "Technician.h"
#include "Computer.h"

RepairTicket::RepairTicket():id(0),description(""),status("open"),computer(nullptr),technician(nullptr){}

RepairTicket::RepairTicket(int id,const std::string& description,Computer* computer):id(id),description(description),status("open"),computer(computer),technician(nullptr){}

bool RepairTicket::assign(Technician* tech){
    if(!tech){
        return false;
    }
    technician=tech;
    status="in_progress";
    return true;
}

bool RepairTicket::close(){
    if(status=="closed"){
        return false;
    }
    status="closed";
    return true;
}

bool RepairTicket::escalate(){
    if(status=="closed"){
        return false;
    }
    description+=" [ESCALATED]";
    return true;
}