/**
 * @file Workstation.h
 * @brief Declaration of the Workstation class.
 */
#pragma once
#include <vector>
#include "Computer.h"

class GPU;

/**
 * @class Workstation
 * @brief Derived class representing a workstation.
 * 
 * Extends the base class Computer by adding support for multiple 
 * graphics cards and the ability to perform rendering tasks.
 */
class Workstation:public Computer{
private:
    int renderJobs;///<Counter of completed rendering tasks.
    std::vector<GPU*> gpus;///<Vector of installed graphics cards.

public:
/**
 * @brief Default constructor.
 */
    Workstation();

/**
 * @brief Constructor with name specification.
 * @param hostname Network name of the workstation.
 */
    explicit Workstation(const std::string& hostname);

/**
 * @brief Adds a graphics card to the system.
 * @param gpu Pointer to the graphics card object.
 */
    void addGpu(GPU* gpu);

/**
 * @brief Performs a rendering task.
 * Distributes the load among the available graphics cards.
 * @param complexity Complexity of the scene to render.
 * @return Rendering execution time in milliseconds (taken from the slowest card).
 * @exception InvalidConfigurationException if there is no graphics card in the system.
 */
    double renderTask(int complexity);
};