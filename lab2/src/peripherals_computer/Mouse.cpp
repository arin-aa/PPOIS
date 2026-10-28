#include "Mouse.h"
#include "ComputerExceptions.h"

const char* const MOUSE_NAME="Mouse";
const int MIN_DPI=100;
const int MAX_DPI=16000;

Mouse::Mouse():Peripheral(MOUSE_NAME),dpi(MIN_DPI),clicks(0){}

Mouse::Mouse(int dpi):Peripheral(MOUSE_NAME),dpi(dpi),clicks(0){}

int Mouse::changeDpi(int newDpi){
    if(newDpi<MIN_DPI || newDpi>MAX_DPI){
        throw InvalidConfigurationException("DPI must be between 100 and 16000");
    }
    dpi=newDpi;
    return dpi;
}

int Mouse::click(){
    ping();
    return ++clicks;
}
