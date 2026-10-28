#include "HDD.h"

const char* const HDD_NAME="HDD";
const int DEFAULT_RPM=5400;
const int MIN_BASE=10800;
const int WEAR_MIN=30;
const int SECTOR_COST=5;
const int LIFE=100;

HDD::HDD():Storage(HDD_NAME,0),rpm(DEFAULT_RPM),badSectors(0),fragmentation(0){}

HDD::HDD(int capacityGb,int rpm,int fragmentation):Storage(HDD_NAME,capacityGb),rpm(rpm>0?rpm:DEFAULT_RPM),badSectors(0),
    fragmentation(fragmentation){}

int HDD::defragment(){
    int minutes=fragmentation*MIN_BASE/rpm;
    fragmentation=0;
    badSectors+=minutes/WEAR_MIN;
    return minutes;
}

int HDD::lifeLeft(){
    int left=LIFE-badSectors*SECTOR_COST;
    return left<0?0:left;
}
