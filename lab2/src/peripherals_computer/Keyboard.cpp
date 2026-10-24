#include "Keyboard.h"

const char* const KEYBOARD_NAME="Keyboard";
const char* const DEFAULT_LAYOUT="QWERTY";

Keyboard::Keyboard():Peripheral(KEYBOARD_NAME),layout(DEFAULT_LAYOUT),isMechanical(false){}

Keyboard::Keyboard(const std::string& layout,bool isMechanical):Peripheral(KEYBOARD_NAME),layout(layout),isMechanical(isMechanical){}

bool Keyboard::changeLayout(const std::string& newLayout){
    if(newLayout.empty()){
        return false;
    }
    layout=newLayout;
    return true;
}

std::string Keyboard::getLayout(){
    return layout;
}
