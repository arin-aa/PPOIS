#include "CPU.h"
#include "ComputerExceptions.h"
#include "Sensor.h"

const int CPU_MAX_PERCENT=100;
const char* const CPU_NAME="CPU";
const char* const CPU_MANUFACTURER="Intel";
const int CPU_POWER_WATTS=65;
const int CPU_LENGTH_MM=40;
const int THROTTLE_LOAD_PERCENT=95;
const double THROTTLE_FACTOR=0.9;

CPU::CPU():Component(CPU_NAME,CPU_MANUFACTURER,CPU_POWER_WATTS,CPU_LENGTH_MM),cores(0),frequencyGhz(0.0),socket(""),tempSensor(nullptr){}

CPU::CPU(const std::string& socket,int cores,double frequencyGhz):Component(CPU_NAME,CPU_MANUFACTURER,CPU_POWER_WATTS,CPU_LENGTH_MM),cores(cores),
    frequencyGhz(frequencyGhz),socket(socket),tempSensor(nullptr){}

std::string CPU::describe(){
    return "CPU "+socket+" "+std::to_string(cores)+"c";
}

void CPU::runLoad(int percent){
    if(percent<=0 || percent>CPU_MAX_PERCENT){
        return;
    }
    if(percent>THROTTLE_LOAD_PERCENT){
        frequencyGhz*=THROTTLE_FACTOR;
    }
    if(isOverheated()){
        throw OverheatingException("CPU temperature is critical");
    }
}

bool CPU::isOverheated(){
    if(!tempSensor){
        return false;
    }
    return tempSensor->isCritical();
}

void CPU::overclock(double newFrequencyGhz){
    if(newFrequencyGhz<=frequencyGhz){
        throw InvalidConfigurationException("overclock must be higher");
    }
    frequencyGhz=newFrequencyGhz;
}

double CPU::getFrequencyGhz(){
    return frequencyGhz;
}
