#include "AppTheme.h"

AppTheme::AppTheme(const std::string& name,bool darkMode,const std::string& accentColor):
    name(name),darkMode(darkMode),accentColor(accentColor){}

bool AppTheme::toggleDarkMode(){
    darkMode=!darkMode;
    return darkMode;
}

const std::string& AppTheme::getAccentColor() const{
    return accentColor;
}