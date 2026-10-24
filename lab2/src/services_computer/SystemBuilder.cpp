#include "SystemBuilder.h"
#include "Case.h"
#include "CompatibilityChecker.h"
#include "Computer.h"
#include "ComputerExceptions.h"
#include "Motherboard.h"
#include "PSU.h"
#include "RAM.h"

const char* const BUILT_HOSTNAME="built-pc";

SystemBuilder::SystemBuilder():checker(nullptr),motherboard(nullptr),psu(nullptr),chassis(nullptr){}

SystemBuilder::SystemBuilder(CompatibilityChecker* checker):checker(checker),motherboard(nullptr),psu(nullptr),chassis(nullptr){}

bool SystemBuilder::installMotherboard(Motherboard* newMotherboard){
    if(!newMotherboard || motherboard){
        return false;
    }
    motherboard=newMotherboard;
    return true;
}

bool SystemBuilder::installPsu(PSU* newPsu){
    if(!newPsu || psu){
        return false;
    }
    psu=newPsu;
    return true;
}

bool SystemBuilder::installCase(Case* newChassis){
    if(!newChassis || chassis){
        return false;
    }
    chassis=newChassis;
    return true;
}

bool SystemBuilder::addRam(RAM* ram){
    if(!ram){
        return false;
    }
    if(checker && motherboard && checker->checkRam(motherboard,ram)<0){
        return false;
    }
    rams.push_back(ram);
    return true;
}

std::unique_ptr<Computer> SystemBuilder::build(){
    if(!motherboard || !psu || !chassis){
        return nullptr;
    }
    if(!chassis->fits(motherboard)){
        throw InvalidConfigurationException("case does not fit the motherboard");
    }
    auto computer=std::make_unique<Computer>(BUILT_HOSTNAME);
    computer->motherboard=motherboard;
    computer->psu=psu;
    computer->chassis=chassis;
    return computer;
}
