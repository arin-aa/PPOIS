#include "AppSettings.h"
#include <stdexcept>

const int DEFAULT_APP_VOLUME=50;
const std::string DEFAULT_LANGUAGE="en";
const std::string DEFAULT_REPEAT_MODE="off";
const std::string DEFAULT_THEME="classic";
const std::string VOLUME_KEY="volume";
const std::string LANGUAGE_KEY="language";
const std::string REPEAT_KEY="repeatMode";
const std::string THEME_KEY="theme";
const std::string CROSSFADE_KEY="crossfadeMs";


AppSettings::AppSettings():
    volume(DEFAULT_APP_VOLUME),language(DEFAULT_LANGUAGE),repeatMode(DEFAULT_REPEAT_MODE),theme(DEFAULT_THEME),crossfadeMs(0){}

bool AppSettings::load(const std::map<std::string,std::string>& values){
    if(values.count(VOLUME_KEY)) volume=std::stoi(values.at(VOLUME_KEY));
    if(values.count(CROSSFADE_KEY)) crossfadeMs=std::stoi(values.at(CROSSFADE_KEY));
    if(values.count(LANGUAGE_KEY)) language=values.at(LANGUAGE_KEY);
    if(values.count(REPEAT_KEY)) repeatMode=values.at(REPEAT_KEY);
    if(values.count(THEME_KEY)) theme=values.at(THEME_KEY);
    return true;
}

int AppSettings::getVolume() const{
    return volume;
}

const std::string& AppSettings::getLanguage() const{
    return language;
}

const std::string& AppSettings::getRepeatMode() const{
    return repeatMode;
}