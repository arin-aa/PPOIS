#include "Technician.h"
#include "RepairTicket.h"
#include "Computer.h"
#include "Component.h"

Technician::Technician():User(),specialization("General"),experienceYears(0){}

Technician::Technician(const std::string& login,const std::string& password,const std::string& specialization,int experienceYears):User(login,password),specialization(specialization),experienceYears(experienceYears){}

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
    return true;
}