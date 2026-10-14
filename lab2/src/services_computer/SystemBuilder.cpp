#include "SystemBuilder.h"
#include "CompatibilityChecker.h"
#include "Motherboard.h"
#include "PSU.h"
#include "Case.h"
#include "RAM.h"
#include "Computer.h"

SystemBuilder::SystemBuilder():checker(nullptr),motherboard(nullptr),psu(nullptr),chassis(nullptr){}

SystemBuilder::SystemBuilder(CompatibilityChecker* checker):checker(checker),motherboard(nullptr),psu(nullptr),chassis(nullptr){}

bool SystemBuilder::installMotherboard(Motherboard* mb){
    if(!mb){
        return false;
    }
    if(motherboard){
        return false;
    }
    motherboard=mb;
    return true;
}

bool SystemBuilder::addRam(RAM* ram){
    if(!ram){
        return false;
    }
    if(checker && motherboard){
        int index=checker->checkRam(motherboard,ram);
        if(index<0){
            return false;
        }
    }
    rams.push_back(ram);
    return true;
}

Computer* SystemBuilder::build(){
    if(!motherboard || !psu || !chassis){
        return nullptr;
    }
    Computer* pc=new Computer("built-pc");
    return pc;
}