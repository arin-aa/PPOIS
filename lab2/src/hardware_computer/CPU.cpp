#include "CPU.h"
#include "Sensor.h"
#include "ComputerExceptions.h"

CPU::CPU():Component("CPU","Intel",65,40),cores(0),frequencyGHz(0.0),socket(""),tempSensor(nullptr){}

CPU::CPU(const std::string& socket,int cores,double ghz):Component("CPU","Intel",65,40),cores(cores),frequencyGHz(ghz),socket(socket),tempSensor(nullptr){}

std::string CPU::describe(){
    return "CPU "+socket+" "+std::to_string(cores)+"c";
}

void CPU::runLoad(int percent){
    if(percent<=0 || percent>100){
        return;
    }
    if(percent>95){
        frequencyGHz*=0.9;
    }
}

bool CPU::isOverheated(){
    if(!tempSensor){
        return false;
    }
    return tempSensor->isCritical();
}

void CPU::overclock(double ghz){
    if(ghz<=frequencyGHz){
        throw InvalidConfigurationException("overclock must be higher");
    }
    frequencyGHz=ghz;
}