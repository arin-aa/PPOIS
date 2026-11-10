/**
 * @file OperatingSystem.h
 * @brief Declaration of the OperatingSystem class.
 */
#pragma once
#include <vector>
#include "Process.h"
#include "Software.h"

class Driver;

/**
 * @class OperatingSystem
 * @brief Operating system class, inheriting from Software.
 * 
 * Manages driver loading and the process lifecycle.
 */
class OperatingSystem:public Software{
private:
    bool isBooted;///<Flag indicating whether the OS is booted.
    int nextPid;///<Next available process identifier.
    std::vector<Process> processes;///<List of running processes.
    std::vector<Driver*> drivers;///<List of installed drivers.

public:
/**
 * @brief Default constructor.
 */
    OperatingSystem();

/**
 * @brief Constructor with parameters.
 * @param name OS name.
 * @param sizeMb OS size in MB.
 */
    OperatingSystem(const std::string& name,int sizeMb);

/**
 * @brief Boots the operating system.
 * @exception BootFailureException if the OS is not installed or contains unsigned drivers.
 */
    void boot();

/**
 * @brief Adds a driver to the system.
 * @param driver Pointer to the driver.
 */
    void addDriver(Driver* driver);

/**
 * @brief Starts a new process.
 * @param process Pointer to the process.
 * @param freeRamMb Available RAM.
 * @return Identifier of the started process.
 * @exception BootFailureException if the OS is not booted yet.
 */
    int startProcess(Process* process,int freeRamMb);

/**
 * @brief Terminates a process by its identifier.
 * @param pid Process identifier.
 * @return Freed memory in MB, or returns -1 if the process is not found.
 */
    int killProcess(int pid);
};