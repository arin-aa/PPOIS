#include "GPU.h"
#include "ComputerExceptions.h"
#include "Sensor.h"

const int GPU_MAX_PERCENT=100;
const char* const GPU_NAME="GPU";
const char* const GPU_MANUFACTURER="NVIDIA";
const int GPU_POWER_WATTS=250;
const int GPU_LENGTH_MM=300;
const double LOAD_BOOST_DIVISOR=200.0;

GPU::GPU():Component(GPU_NAME,GPU_MANUFACTURER,GPU_POWER_WATTS,GPU_LENGTH_MM),vramGb(0),coreClockMhz(0),tempSensor(nullptr){}

GPU::GPU(int vramGb,int coreClockMhz):Component(GPU_NAME,GPU_MANUFACTURER,GPU_POWER_WATTS,GPU_LENGTH_MM),vramGb(vramGb),coreClockMhz(coreClockMhz),
    tempSensor(nullptr){}

std::string GPU::describe(){
    return "GPU "+std::to_string(vramGb)+"GB";
}

void GPU::runLoad(int percent){
    if(percent<=0 || percent>GPU_MAX_PERCENT){
        return;
    }
    double boostFactor=1.0+percent/LOAD_BOOST_DIVISOR;
    coreClockMhz=static_cast<int>(coreClockMhz*boostFactor);
    if(tempSensor && tempSensor->isCritical()){
        throw OverheatingException("GPU temperature is critical");
    }
}

bool GPU::isSufficientFor(int neededVram){
    return vramGb>=neededVram;
}
