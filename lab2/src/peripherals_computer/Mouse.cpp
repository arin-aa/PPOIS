#include "Mouse.h"

Mouse::Mouse():Peripheral("Mouse"),dpi(800),buttonsCount(3){}

Mouse::Mouse(int dpi,int buttonsCount):Peripheral("Mouse"),dpi(dpi),buttonsCount(buttonsCount){}

bool Mouse::setDpi(int newDpi){
    if(newDpi<100 || newDpi>30000){
        return false;
    }
    dpi=newDpi;
    return true;
}