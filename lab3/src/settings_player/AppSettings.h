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
 * If any value is invalid nothing is changed.
 * @param values Text values by key.
 * @return true if all values were accepted.
 */
    bool load(const std::map<std::string,std::string>& values);

/**
 * @brief Returns the volume.
 * @return Default volume.
 */
    int getVolume() const;

/**
 * @brief Returns the language.
 * @return Language code.
 */
    const std::string& getLanguage() const;

/**
 * @brief Returns the repeat mode.
 * @return Default repeat mode.
 */
    const std::string& getRepeatMode() const;
};