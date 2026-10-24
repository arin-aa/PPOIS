#pragma once
#include <string>

class Computer;
class Technician;

class RepairTicket{
private:
    int id;
    std::string description;
    std::string status;
    Computer* computer;
    Technician* technician;

public:
    RepairTicket();
    RepairTicket(int id,const std::string& description,Computer* computer);

    bool assign(Technician* assignee);
    bool close();
    bool escalate();
    std::string getStatus();
    std::string getDescription();

    friend class Technician;
};
