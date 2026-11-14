/**
 * @file Case.h
 * @brief Declaration of the Case class.
 */
#pragma once
#include <vector>
#include "Component.h"

class Fan;

/**
 * @class Case
 * @brief Class representing a computer case, inheriting from Component.
 */
class Case:public Component{
private:
    int maxFans;///<Maximum number of fans.
    int dustLevel;///<Dust level.
    std::vector<Fan*> fans;///<Installed fans.

public:
/**
 * @brief Default constructor.
 */
    Case();

/**
 * @brief Constructor with maximum number of fans specified.
 * @param maxFans Maximum number of fans.
 */ 
    explicit Case(int maxFans);

/**
 * @brief Installs a fan into the case.
 * @param fan Pointer to the fan.
 * @exception InvalidConfigurationException if all slots are occupied.
 */
    void addFan(Fan* fan);

/**
 * @brief Calculates total airflow taking dust level into account.
 * @return Total airflow.
 */
    int totalAirflow();
};