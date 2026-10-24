#include "Technician.h"
#include "Component.h"
#include "Computer.h"
#include "RepairTicket.h"

const char* const DEFAULT_SPECIALIZATION="General";
const char* const REPLACEMENT_MARK=" replaced: ";

Technician::Technician():User(),specialization(DEFAULT_SPECIALIZATION),experienceYears(0){}

Technician::Technician(const std::string& login,const std::string& password,const std::string& specialization,int experienceYears):
    User(login,password),specialization(specialization),experienceYears(experienceYears){}

bool Technician::acceptTicket(RepairTicket* ticket){
    if(!ticket){
        return false;
    }
    tickets.push_back(ticket);
    ticket->assign(this);
    return true;
}

bool Technician::repair(Computer* computer,Component* newComponent){
    if(!computer || !newComponent){
        return false;
    }
    for(RepairTicket* ticket:tickets){
        if(ticket->computer==computer){
            ticket->description+=REPLACEMENT_MARK+newComponent->describe();
            return ticket->close();
        }
    }
    return false;
}

int Technician::getTicketCount(){
    return static_cast<int>(tickets.size());
}
