#include "Workstation.h"
#include "Cooler.h"
#include "GPU.h"

const int WORKSTATION_NOT_AVAILABLE=-1;

Workstation::Workstation():Computer(){}

Workstation::Workstation(const std::string& hostname):Computer(hostname){}

void Workstation::installGpu(GPU* newGpu){
    if(!newGpu){
        return;
    }
    gpus.push_back(newGpu);
}

int Workstation::renderTask(int complexity){
    if(gpus.empty() || complexity<=0){
        return WORKSTATION_NOT_AVAILABLE;
    }
    return complexity/static_cast<int>(gpus.size());
}
