#include "Technician.h"
#include "Component.h"
#include "ComputerExceptions.h"
#include "Inventory.h"

const char* const HARDWARE="hardware";
const int BASE_RATE=20;
const int YEAR_BONUS=2;
const int HARDWARE_BONUS=10;

Technician::Technician():User(),specialization(""),experienceYears(0),repairsDone(0){}

Technician::Technician(const std::string& login,const std::string& password,const std::string& specialization,int experienceYears):
    User(login,password),specialization(specialization),experienceYears(experienceYears),repairsDone(0){}

int Technician::estimate(int hours){
    int rate=BASE_RATE+experienceYears*YEAR_BONUS;
    if(specialization==HARDWARE){
        rate+=HARDWARE_BONUS;
    }
    return hours*rate;
}

Component* Technician::orderPart(Inventory* stock,const std::string& key){
    Component* part=stock->takeItem(key);
    if(!part){
        throw InvalidConfigurationException(key+" is not in stock");
    }
    repairsDone++;
    return part;
}
