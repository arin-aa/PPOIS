#pragma once
#include <string>
#include <vector>
#include "User.h"

class RepairTicket;
class Computer;
class Component;

class Technician:public User{
private:
    std::string specialization;
    int experienceYears;
    std::vector<RepairTicket*> tickets;

public:
    Technician();
    Technician(const std::string& login,const std::string& password,const std::string& specialization,int experienceYears);

    bool acceptTicket(RepairTicket* ticket);
    bool repair(Computer* computer,Component* newComponent);
};