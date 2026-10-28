#include "Workstation.h"
#include "ComputerExceptions.h"
#include "GPU.h"

Workstation::Workstation():Computer(),renderJobs(0){}

Workstation::Workstation(const std::string& hostname):Computer(hostname),renderJobs(0){}

void Workstation::addGpu(GPU* gpu){
    gpus.push_back(gpu);
}

double Workstation::renderTask(int complexity){
    if(gpus.empty()){
        throw InvalidConfigurationException(hostname+" has no GPU to render on");
    }
    int share=complexity/static_cast<int>(gpus.size());
    double slowest=0.0;
    for(GPU* gpu:gpus){
        double time=gpu->renderTime(share);
        if(time>slowest){
            slowest=time;
        }
    }
    renderJobs++;
    return slowest;
}
