#include "Fan.h"

Fan::Fan():Component("Fan","Noctua",2,25),rpm(0),sizeMm(0){}

Fan::Fan(int sizeMm):Component("Fan","Noctua",2,25),rpm(0),sizeMm(sizeMm){}

std::string Fan::describe(){
    return "Fan "+std::to_string(sizeMm)+"mm";
}

void Fan::setSpeed(int newRpm){
    if(newRpm<0){
        return;
    }
    rpm=newRpm;
}