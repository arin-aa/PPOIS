#include "Keyboard.h"
#include "ComputerExceptions.h"

const char* const KB_NAME="Keyboard";
const char* const EN="EN";
const char* const RU="RU";
const char* const DE="DE";

Keyboard::Keyboard():Peripheral(KB_NAME),layout(EN),keyPresses(0){}

Keyboard::Keyboard(const std::string& layout):Peripheral(KB_NAME),layout(layout),keyPresses(0){}

void Keyboard::switchLayout(const std::string& newLayout){
    if(newLayout!=EN && newLayout!=RU && newLayout!=DE){
        throw InvalidConfigurationException("unsupported layout "+newLayout);
    }
    layout=newLayout;
}

int Keyboard::press(int count){
    ping();
    keyPresses+=count;
    return keyPresses;
}
