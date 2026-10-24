#include "Motherboard.h"
#include "Chipset.h"
#include "ComputerExceptions.h"
#include "CPU.h"
#include "Port.h"
#include "RAM.h"

const char* const MOTHERBOARD_NAME="MB";
const char* const MOTHERBOARD_MANUFACTURER="ASUS";
const int MOTHERBOARD_POWER_WATTS=80;
const int MOTHERBOARD_LENGTH_MM=305;

Motherboard::Motherboard():Component(MOTHERBOARD_NAME,MOTHERBOARD_MANUFACTURER,MOTHERBOARD_POWER_WATTS,MOTHERBOARD_LENGTH_MM),socket(""),ramSlots(0),
    formFactor(""),chipset(nullptr),cpu(nullptr){}

Motherboard::Motherboard(const std::string& socket,int ramSlots,const std::string& formFactor):
    Component(MOTHERBOARD_NAME,MOTHERBOARD_MANUFACTURER,MOTHERBOARD_POWER_WATTS,MOTHERBOARD_LENGTH_MM),socket(socket),ramSlots(ramSlots),
    formFactor(formFactor),chipset(nullptr),cpu(nullptr){}

std::string Motherboard::describe(){
    return "Motherboard "+socket;
}

bool Motherboard::installCpu(CPU* newCpu){
    if(!newCpu || cpu){
        return false;
    }
    if(newCpu->socket!=socket){
        throw IncompatibleSocketException("CPU socket does not match motherboard");
    }
    cpu=newCpu;
    return true;
}

bool Motherboard::installRam(RAM* ram){
    if(!ram || !hasFreeRamSlot()){
        return false;
    }
    ramModules.push_back(ram);
    return true;
}

bool Motherboard::hasFreeRamSlot(){
    return static_cast<int>(ramModules.size())<ramSlots;
}
