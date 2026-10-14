#include "Keyboard.h"

Keyboard::Keyboard():Peripheral("Keyboard"),layout("QWERTY"),isMechanical(false){}

Keyboard::Keyboard(const std::string& layout,bool isMechanical):Peripheral("Keyboard"),layout(layout),isMechanical(isMechanical){}

bool Keyboard::changeLayout(const std::string& newLayout){
    if(newLayout.empty()){
        return false;
    }
    layout=newLayout;
    return true;
}