#include "CrossfadeSettings.h"

CrossfadeSettings::CrossfadeSettings(int durationMs):durationMs(durationMs){}

bool CrossfadeSettings::isEnabled() const{
    return durationMs>0;
}