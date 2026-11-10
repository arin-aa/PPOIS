/**
 * @file Computer.h
 * @brief Declaration of the base class Computer.
 */
#pragma once
#include <string>
#include <vector>

class Motherboard;
class PSU;
class Storage;
class OperatingSystem;

/**
 * @class Computer
 * @brief Class representing a personal computer.
 * 
 * Stores information about components (motherboard, power supply, storage devices),
 * allows assembling the system, installing an OS, and calculating power consumption.
 * Is a base class for Laptop, Server, and Workstation.
 */
class Computer{
protected:
    std::string hostname;///<Network name of the computer.
    int bootCount;///<Number of successful boots.
    Motherboard* motherboard;///<Pointer to the motherboard.
    PSU* psu;///<Pointer to the power supply.
    OperatingSystem* os;///<Pointer to the installed operating system.
    std::vector<Storage*> storages;///<Vector of installed storage devices.

public:
/**
 * @brief Default constructor.
 * Creates a PC with an empty name and null pointers.
 */
    Computer();

/**
 * @brief Constructor with name specification.
 * @param hostname Network name of the computer.
 */
    explicit Computer(const std::string& hostname);

/**
 * @brief Virtual default destructor.
 */
    virtual ~Computer()=default;

/**
 * @brief Assembles the computer by installing the motherboard and power supply.
 * @param board Pointer to the motherboard.
 * @param supply Pointer to the power supply.
 */
    void assemble(Motherboard* board,PSU* supply);

/**
 * @brief Adds a storage device to the system.
 * @param storage Pointer to the storage object.
 */
    void addStorage(Storage* storage);

/**
 * @brief Installs the operating system.
 * @param newOs Pointer to the OS to be installed.
 * @exception InvalidConfigurationException if there is no storage device in the system.
 */   
    void installOs(OperatingSystem* newOs);

/**
 * @brief Powers on the computer.
 * @exception BootFailureException if the computer is not assembled (no motherboard or PSU).
 * @exception InsufficientPowerException if the PSU power is insufficient.
 */   
    void powerOn();

/**
 * @brief Calculates the total free space on all storage devices.
 * @return Total free space in gigabytes.
 */
    int freeStorageGb();

/**
 * @brief Calculates the current power consumption of the computer.
 * @return Power consumption in watts. Can be overridden in derived classes.
 */  
    virtual int powerDraw();

/**
 * @brief Calculates the power reserve of the power supply.
 * @return Difference between PSU power and current consumption (in watts).
 * @exception BootFailureException if the power supply is not installed.
 */
    int powerReserve();
};