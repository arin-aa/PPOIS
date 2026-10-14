#include "Motherboard.h"
#include "CPU.h"
#include "RAM.h"
#include "Chipset.h"
#include "Port.h"

Motherboard::Motherboard():Component("MB","ASUS",80,305),socket(""),ramSlots(0),formFactor(""),chipset(nullptr),cpu(nullptr){}

Motherboard::Motherboard(const std::string& socket,int ramSlots,const std::string& formFactor):Component("MB","ASUS",80,305),socket(socket),ramSlots(ramSlots),formFactor(formFactor),chipset(nullptr),cpu(nullptr){}

std::string Motherboard::describe(){
    return "Motherboard "+socket;
}

bool Motherboard::installCpu(CPU* newCpu){
    if(!newCpu){
        return false;
    }
    if(cpu){
        return false;
    }
    if(newCpu->socket!=socket){
        return false;
    }
    cpu=newCpu;
    return true;
}

bool Motherboard::installRam(RAM* ram){
    if(!ram){
        return false;
    }
    if((int)ramModules.size()>=ramSlots){
        return false;
    }
    ramModules.push_back(ram);
    return true;
}

bool Motherboard::hasFreeRamSlot(){
    return (int)ramModules.size()<ramSlots;
}