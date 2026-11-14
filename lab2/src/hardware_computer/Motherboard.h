/**
 * @file Motherboard.h
 * @brief Declaration of the Motherboard class.
 */
#pragma once
#include <string>
#include <vector>
#include "Component.h"

class CPU;
class RAM;

/**
 * @class Motherboard
 * @brief Motherboard class.
 */
class Motherboard:public Component{
private:
    std::string socket;///<Socket type.
    int ramSlots;///<Number of RAM slots.
    CPU* cpu;///<Installed processor.
    std::vector<RAM*> ramModules;///<Installed RAM modules.

public:
/**
 * @brief Default constructor.
 */
    Motherboard();

/**
 * @brief Constructor with parameters.
 * @param socket Socket.
 * @param ramSlots Number of slots.
 */
    Motherboard(const std::string& socket,int ramSlots);

/**
 * @brief Installs the processor.
 * @param newCpu Pointer to the processor.
 */ 
    void installCpu(CPU* newCpu);

/**
 * @brief Installs a RAM module.
 * @param ram Pointer to the module.
 * @exception InvalidConfigurationException if there are no free slots.
 */
    void installRam(RAM* ram);

/**
 * @brief Returns the total amount of free RAM.
 * @return Amount in GB.
 */ 
    int freeRamGb();
};