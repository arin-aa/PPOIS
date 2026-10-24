#include "Mouse.h"

const char* const MOUSE_NAME="Mouse";
const int DEFAULT_DPI=800;
const int DEFAULT_BUTTONS=3;
const int MIN_DPI=100;
const int MAX_DPI=30000;

Mouse::Mouse():Peripheral(MOUSE_NAME),dpi(DEFAULT_DPI),buttonsCount(DEFAULT_BUTTONS){}

Mouse::Mouse(int dpi,int buttonsCount):Peripheral(MOUSE_NAME),dpi(dpi),buttonsCount(buttonsCount){}

bool Mouse::setDpi(int newDpi){
    if(newDpi<MIN_DPI || newDpi>MAX_DPI){
        return false;
    }
    dpi=newDpi;
    return true;
}

int Mouse::getDpi(){
    return dpi;
}
