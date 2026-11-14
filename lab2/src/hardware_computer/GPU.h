/**
 * @file GPU.h
 * @brief Declaration of the GPU class.
 */
#pragma once
#include "Component.h"

/**
 * @class GPU
 * @brief Graphics card class.
 */
class GPU:public Component{
private:
    int vramGb;///<Video memory size in GB.
    int coreClockMhz;///<Core clock in MHz.
    int framesRendered;///<Number of rendered frames.

public:
/**
 * @brief Default constructor.
 */
    GPU();

/**
 * @brief Constructor with parameters.
 * @param vramGb Memory size.
 * @param coreClockMhz Clock speed.
 */ 
    GPU(int vramGb,int coreClockMhz);

/**
 * @brief Calculates scene rendering time.
 * @param complexity Scene complexity.
 * @return Rendering time in ms.
 * @exception MemoryOverflowException if the scene does not fit into VRAM.
 */
    double renderTime(int complexity);
};