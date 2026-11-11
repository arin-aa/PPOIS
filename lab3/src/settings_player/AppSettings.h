/**
 * @file AppSettings.h
 * @brief Declaration of the AppSettings class.
 */
#pragma once
#include <map>
#include <string>

/**
 * @class AppSettings
 * @brief General preferences of the application that can be loaded from text values.
 */
class AppSettings{
private:
    int volume;///<Default volume from 0 to 100.
    std::string language;///<Interface language code: "en", "ru" or "de".
    std::string repeatMode;///<Default repeat mode: "off", "one" or "all".
    std::string theme;///<Name of the theme of the application.
    int crossfadeMs;///<Default crossfade length in milliseconds.

public:
/**
 * @brief Default constructor. Settings get their default values.
 */
    AppSettings();

/**
 * @brief Loads values from text. Keys that are absent keep their value.
 *
 * Supported keys: volume, language, repeatMode, theme, crossfadeMs.
 * @param values Text values by key.
 * @exception std::invalid_argument if a numeric value is not a number.
 */
    void load(const std::map<std::string,std::string>& values);
};