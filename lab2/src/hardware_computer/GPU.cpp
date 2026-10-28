#include "GPU.h"
#include "ComputerExceptions.h"

const char* const GPU_NAME="GPU";
const char* const GPU_MAKER="NVIDIA";
const int GPU_WATTS=200;
const int COMPLEXITY_PER_GB=100;
const int TIME_SCALE=1000;

GPU::GPU():Component(GPU_NAME,GPU_MAKER,GPU_WATTS),vramGb(0),coreClockMhz(1),framesRendered(0){}

GPU::GPU(int vramGb,int coreClockMhz):Component(GPU_NAME,GPU_MAKER,GPU_WATTS),vramGb(vramGb),coreClockMhz(coreClockMhz),framesRendered(0){}

double GPU::renderTime(int complexity){
    if(complexity>vramGb*COMPLEXITY_PER_GB){
        throw MemoryOverflowException("scene does not fit into video memory");
    }
    framesRendered++;
    return static_cast<double>(complexity)*TIME_SCALE/coreClockMhz;
}
