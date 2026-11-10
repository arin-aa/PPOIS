/**
 * @file Component.h
 * @brief Declaration of the base class Component.
 */
#pragma once
#include <string>

/**
 * @class Component
 * @brief Base class for all computer components.
 * 
 * Contains common properties (name, manufacturer, power consumption) 
 * and methods for identification and load calculation.
 */
class Component{
protected:
    std::string name;///<Component name.
    std::string manufacturer;///<Manufacturer.
    int powerWatts;///<Power consumption

public:
/**
 * @brief Default constructor.
 */
    Component();

/**
 * @brief Constructor with parameters.
 * @param name Component name.
 * @param manufacturer Manufacturer.
 * @param powerWatts Power consumption (in watts).
 */
    Component(const std::string& name,const std::string& manufacturer,int powerWatts);

/**
 * @brief Virtual default destructor.
 */
    virtual ~Component()=default;

/**
 * @brief Checks whether the passed string matches the name or manufacturer.
 * @param key The string to search for.
 * @return true if a match is found.
 */
    bool isNamed(const std::string& key);

/**
 * @brief Calculates current power consumption taking load into account.
 * @param loadPercent Load percentage.
 * @return Power consumption.
 */
    int draw(int loadPercent);
};