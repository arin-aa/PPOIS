/**
 * @file Application.h
 * @brief Declaration of the Application class.
 */
#pragma once
#include "Software.h"

/**
 * @class Application
 * @brief User application class, inheriting from Software.
 */
class Application:public Software{
private:
    int requiredRamMb;///<Required amount of RAM.
    std::string licenseKey;//<Application license key.
    int launches;///<Counter of successful launches.

public:
/**
 * @brief Default constructor.
 */
    Application();

/**
 * @brief Constructor with parameters.
 * @param name Application name.
 * @param sizeMb Size in MB.
 * @param requiredRamMb Required RAM.
 * @param licenseKey License key.
 */
    Application(const std::string& name,int sizeMb,int requiredRamMb,const std::string& licenseKey);

/**
 * @brief Checks the validity of the license key.
 * @param key The key to check.
 * @return true if the key matches and is not empty.
 */
    bool checkLicense(const std::string& key);

/**
 * @brief Launches the application.
 * @param freeRamMb Available free RAM.
 * @return Remaining free memory after launch.
 * @exception InvalidConfigurationException if the application is not installed.
 * @exception MemoryOverflowException if there is not enough RAM.
 */
    int launch(int freeRamMb);
};