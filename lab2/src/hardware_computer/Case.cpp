#include "Case.h"
#include "ComputerExceptions.h"
#include "Fan.h"

const char* const CASE_NAME="Case";
const char* const CASE_MAKER="NZXT";
const int CASE_WATTS=0;
const int DUST_STEP=5;
const int DUST_LIMIT=50;

Case::Case():Component(CASE_NAME,CASE_MAKER,CASE_WATTS),maxFans(0),dustLevel(0){}

Case::Case(int maxFans):Component(CASE_NAME,CASE_MAKER,CASE_WATTS),maxFans(maxFans),dustLevel(0){}

void Case::addFan(Fan* fan){
    if(static_cast<int>(fans.size())>=maxFans){
        throw InvalidConfigurationException("no free fan mounts in the case");
    }
    fans.push_back(fan);
    dustLevel+=DUST_STEP;
}

int Case::totalAirflow(){
    int flow=0;
    for(Fan* fan:fans){
        flow+=fan->airflow();
    }
    return dustLevel>DUST_LIMIT?flow/2:flow;
}
