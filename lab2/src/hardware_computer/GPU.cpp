#include "GPU.h"
#include "Sensor.h"

GPU::GPU():Component("GPU","NVIDIA",250,300),vramGb(0),coreClockMhz(0),tempSensor(nullptr){}

GPU::GPU(int vramGb,int coreClockMhz):Component("GPU","NVIDIA",250,300),vramGb(vramGb),coreClockMhz(coreClockMhz),tempSensor(nullptr){}

std::string GPU::describe(){
    return "GPU "+std::to_string(vramGb)+"GB";
}

void GPU::runLoad(int percent){
    if(percent<=0 || percent>100){
        return;
    }
    coreClockMhz=(int)(coreClockMhz*(1.0+percent/200.0));
}

bool GPU::isSufficientFor(int neededVram){
    return vramGb>=neededVram;
}