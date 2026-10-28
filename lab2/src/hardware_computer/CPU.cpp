#include "CPU.h"
#include "ComputerExceptions.h"
#include "Sensor.h"

const char* const CPU_NAME="CPU";
const char* const CPU_MAKER="Intel";
const int CPU_WATTS=65;
const int MAX_LOAD=100;
const int HOT_LOAD=95;
const double THROTTLE=0.9;

CPU::CPU():Component(CPU_NAME,CPU_MAKER,CPU_WATTS),cores(0),frequencyGhz(0.0),loadPercent(0),socket(""),tempSensor(nullptr){}

CPU::CPU(const std::string& socket,int cores,double frequencyGhz,Sensor* tempSensor):Component(CPU_NAME,CPU_MAKER,CPU_WATTS),cores(cores),
    frequencyGhz(frequencyGhz),loadPercent(0),socket(socket),tempSensor(tempSensor){}

void CPU::runLoad(int percent){
    if(percent<0 || percent>MAX_LOAD){
        throw InvalidConfigurationException("load must be between 0 and 100");
    }
    loadPercent=percent;
    if(percent>HOT_LOAD){
        frequencyGhz*=THROTTLE;
    }
    if(tempSensor && tempSensor->margin()<=0){
        throw OverheatingException("CPU temperature is critical");
    }
}

void CPU::checkSocket(const std::string& boardSocket){
    if(socket!=boardSocket){
        throw IncompatibleSocketException(std::to_string(cores)+"-core CPU needs socket "+socket+", board has "+boardSocket);
    }
}
