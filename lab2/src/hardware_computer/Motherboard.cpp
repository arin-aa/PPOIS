#include "Motherboard.h"
#include "ComputerExceptions.h"
#include "CPU.h"
#include "RAM.h"

const char* const BOARD_NAME="Motherboard";
const char* const BOARD_MAKER="ASUS";
const int BOARD_WATTS=40;

Motherboard::Motherboard():Component(BOARD_NAME,BOARD_MAKER,BOARD_WATTS),socket(""),ramSlots(0),cpu(nullptr){}

Motherboard::Motherboard(const std::string& socket,int ramSlots):Component(BOARD_NAME,BOARD_MAKER,BOARD_WATTS),socket(socket),
    ramSlots(ramSlots),cpu(nullptr){}

void Motherboard::installCpu(CPU* newCpu){
    newCpu->checkSocket(socket);
    cpu=newCpu;
}

void Motherboard::installRam(RAM* ram){
    if(static_cast<int>(ramModules.size())>=ramSlots){
        throw InvalidConfigurationException("all RAM slots are taken");
    }
    ramModules.push_back(ram);
}

int Motherboard::freeRamGb(){
    int freeGb=0;
    for(RAM* ram:ramModules){
        freeGb+=ram->freeGb();
    }
    return freeGb;
}
