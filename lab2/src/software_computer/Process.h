/**
 * @file Process.h
 * @brief Declaration of the Process class.
 */
#pragma once
#include <string>

class Application;

/**
 * @class Process
 * @brief Class representing a running application process.
 */
class Process{
private:
    int ramUsageMb;///<Amount of RAM used.
    std::string state;///<Current process state ("new", "running", "stopped").
    Application* app;///<Pointer to the running application.

public:
/**
 * @brief Default constructor.
 */
    Process();

/**
 * @brief Constructor with application specified.
 * @param app Pointer to the application.
 */
    explicit Process(Application* app);


/**
 * @brief Starts the process.
 * @param freeRamMb Available RAM.
 * @return Amount of memory occupied by the process.
 * @exception MemoryOverflowException if the application does not have enough memory.
 */
    int start(int freeRamMb);

/**
 * @brief Terminates the process.
 * @return Amount of freed RAM.
 */
    int terminate();
};