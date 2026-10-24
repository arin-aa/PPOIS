#include "Chipset.h"
#include "CPU.h"

const char* const SOCKET_LGA1700="LGA1700";
const char* const SOCKET_AM5="AM5";
const char* const CHIPSET_Z790="Z790";
const char* const CHIPSET_B650="B650";

Chipset::Chipset():model(""),maxPcieLanes(0){}

Chipset::Chipset(const std::string& model,int maxPcieLanes):model(model),maxPcieLanes(maxPcieLanes){}

bool Chipset::supportsCpu(CPU* cpu){
    if(!cpu){
        return false;
    }
    if(model==CHIPSET_Z790){
        return cpu->socket==SOCKET_LGA1700;
    }
    if(model==CHIPSET_B650){
        return cpu->socket==SOCKET_AM5;
    }
    return false;
}
