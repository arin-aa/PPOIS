/**
 * @file AppTheme.h
 * @brief Declaration of the AppTheme class.
 */
#pragma once
#include <string>

/**
 * @class AppTheme
 * @brief Look of the application.
 */
class AppTheme{
private:
    std::string name;///<Name of the theme.
    bool darkMode;///<Whether dark colors are used.
    std::string accentColor;///<Accent color in the form "#RRGGBB".

public:
/**
 * @brief Constructor with parameters.
 * @param name Name of the theme.
 * @param darkMode Whether dark colors are used.
 * @param accentColor Accent color in the form "#RRGGBB".
 */
    AppTheme(const std::string& name,bool darkMode,const std::string& accentColor);

/**
 * @brief Switches between light and dark colors.
 * @return true if the dark mode is on after the switch.
 */
    bool toggleDarkMode();

/**
 * @brief Returns the accent color.
 * @return Color in the form "#RRGGBB".
 */
    const std::string& getAccentColor() const;
};