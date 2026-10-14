#include "Workstation.h"
#include "GPU.h"
#include "Cooler.h"

Workstation::Workstation():Computer(){}

Workstation::Workstation(const std::string& hostname):Computer(hostname){}

void Workstation::installGpu(GPU* newGpu){
    if(!newGpu){
        return;
    }
    gpu.push_back(newGpu);
}

int Workstation::renderTask(int complexity){
    if(gpu.empty() || complexity<=0){
        return -1;
    }
    return complexity/(int)gpu.size();
}
