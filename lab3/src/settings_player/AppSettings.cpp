#include "AppSettings.h"
#include "DefaultSettings.h"

const std::string DEFAULT_LANGUAGE="en";
const std::string DEFAULT_THEME="classic";
const int DEFAULT_CROSSFADE_MS=0;
const std::string VOLUME_KEY="volume";
const std::string LANGUAGE_KEY="language";
const std::string REPEAT_KEY="repeatMode";
const std::string THEME_KEY="theme";
const std::string CROSSFADE_KEY="crossfadeMs";

AppSettings::AppSettings():
    volume(DEFAULT_VOLUME),language(DEFAULT_LANGUAGE),repeatMode(DEFAULT_REPEAT_MODE),theme(DEFAULT_THEME),
    crossfadeMs(DEFAULT_CROSSFADE_MS){}

void AppSettings::load(const std::map<std::string,std::string>& values){
    if(values.count(VOLUME_KEY)){
        volume=std::stoi(values.at(VOLUME_KEY));
    }
    if(values.count(CROSSFADE_KEY)){
        crossfadeMs=std::stoi(values.at(CROSSFADE_KEY));
    }
    if(values.count(LANGUAGE_KEY)){
        language=values.at(LANGUAGE_KEY);
    }
    if(values.count(REPEAT_KEY)){
        repeatMode=values.at(REPEAT_KEY);
    }
    if(values.count(THEME_KEY)){
        theme=values.at(THEME_KEY);
    }
}