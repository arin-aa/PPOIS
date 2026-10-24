#include "Case.h"
#include "Fan.h"
#include "Motherboard.h"

const char* const FORM_FACTOR_ATX="ATX";
const char* const FORM_FACTOR_MICRO_ATX="mATX";
const char* const CASE_NAME="Case";
const char* const CASE_MANUFACTURER="NZXT";
const int CASE_POWER_WATTS=10;
const int CASE_LENGTH_MM=450;
const int MAX_FANS=6;

Case::Case():Component(CASE_NAME,CASE_MANUFACTURER,CASE_POWER_WATTS,CASE_LENGTH_MM),formFactor(""),maxGpuLengthMm(0){}

Case::Case(const std::string& formFactor,int maxGpuLengthMm):Component(CASE_NAME,CASE_MANUFACTURER,CASE_POWER_WATTS,CASE_LENGTH_MM),
    formFactor(formFactor),maxGpuLengthMm(maxGpuLengthMm){}

std::string Case::describe(){
    return "Case "+formFactor;
}

bool Case::fits(Motherboard* board){
    if(!board){
        return false;
    }
    if(board->formFactor==FORM_FACTOR_ATX){
        return formFactor==FORM_FACTOR_ATX;
    }
    if(board->formFactor==FORM_FACTOR_MICRO_ATX){
        return formFactor==FORM_FACTOR_ATX || formFactor==FORM_FACTOR_MICRO_ATX;
    }
    return false;
}

bool Case::addFan(Fan* fan){
    if(!fan){
        return false;
    }
    if(static_cast<int>(fans.size())>=MAX_FANS){
        return false;
    }
    fans.push_back(fan);
    return true;
}

int Case::getFanCount(){
    return static_cast<int>(fans.size());
}
