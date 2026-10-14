#include "Chipset.h"
#include "CPU.h"

Chipset::Chipset():model(""),maxPcieLanes(0){}

Chipset::Chipset(const std::string& model,int maxPcieLanes):model(model),maxPcieLanes(maxPcieLanes){}

bool Chipset::supportsCpu(CPU* cpu){
    if(!cpu){
        return false;
    }
    if(model=="Z790" && cpu->socket=="LGA1700"){
        return true;
    }
    if(model=="B650" && cpu->socket=="AM5"){
        return true;
    }
    return false;
}