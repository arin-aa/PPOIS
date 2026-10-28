#include "RAM.h"
#include "ComputerExceptions.h"

const char* const RAM_NAME="RAM";
const char* const RAM_MAKER="Kingston";
const int RAM_WATTS=5;
const int FILL_MS=8000;

RAM::RAM():Component(RAM_NAME,RAM_MAKER,RAM_WATTS),capacityGb(0),usedGb(0),speedMhz(1){}

RAM::RAM(int capacityGb,int speedMhz):Component(RAM_NAME,RAM_MAKER,RAM_WATTS),capacityGb(capacityGb),usedGb(0),speedMhz(speedMhz){}

int RAM::allocate(int gb){
    if(usedGb+gb>capacityGb){
        throw MemoryOverflowException("not enough free memory");
    }
    usedGb+=gb;
    return gb*FILL_MS/speedMhz;
}

int RAM::freeGb(){
    return capacityGb-usedGb;
}
