/**
 * @file Technician.h
 * @brief Declaration of the Technician class.
 */
#pragma once
#include "User.h"

class Inventory;
class Component;

/**
 * @class Technician
 * @brief Technician class, inheriting from User.
 * 
 * Represents a service center employee who can perform repairs 
 * and order parts from the warehouse.
 */
class Technician:public User{
private:
    std::string specialization;///<Technician specialization.
    int experienceYears;///<Work experience in years.
    int repairsDone;///<Number of completed repairs.

public:
/**
 * @brief Default constructor.
 */
    Technician();

/**
 * @brief Constructor with parameters.
 * @param login Login.
 * @param password Password.
 * @param specialization Specialization.
 * @param experienceYears Experience.
 */
    Technician(const std::string& login,const std::string& password,const std::string& specialization,int experienceYears);

/**
 * @brief Calculates the cost of the technician's work.
 * @param hours Number of hours spent.
 * @return Total cost.
 */
    int estimate(int hours);

/**
 * @brief Orders a part from the warehouse.
 * @param stock Pointer to the warehouse.
 * @param key The search key (name or manufacturer).
 * @return Pointer to the received part.
 * @exception InvalidConfigurationException if the part is not in the warehouse.
 */
    Component* orderPart(Inventory* stock,const std::string& key);
};