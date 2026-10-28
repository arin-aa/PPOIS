#include "SystemBuilder.h"
#include "CompatibilityChecker.h"
#include "ComputerExceptions.h"

const int PSU_STEP=50;
const int REDUNDANCY_NUM=3;
const int REDUNDANCY_DEN=2;

SystemBuilder::SystemBuilder():budget(0),spent(0),partsWatts(0),checker(nullptr){}

SystemBuilder::SystemBuilder(int budget,CompatibilityChecker* checker):budget(budget),spent(0),partsWatts(0),checker(checker){}

void SystemBuilder::addPart(int watts,int price){
    if(spent+price>budget){
        throw InvalidConfigurationException("the part is over the budget");
    }
    spent+=price;
    partsWatts+=watts;
}

int SystemBuilder::powerMargin(int psuWatts){
    return checker->checkPower(psuWatts,partsWatts);
}

int SystemBuilder::recommendedPsu(){
    int wanted=partsWatts*REDUNDANCY_NUM/REDUNDANCY_DEN;
    return (wanted+PSU_STEP-1)/PSU_STEP*PSU_STEP;
}
