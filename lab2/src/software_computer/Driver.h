/**
 * @file Driver.h
 * @brief Declaration of the Driver class.
 */
#pragma once
#include "Software.h"

class Component;

/**
 * @class Driver
 * @brief Device driver class, inheriting from Software.
 */
class Driver:public Software{
private:
    std::string deviceName;///<Name of the device the driver is intended for.
    bool isSigned;///<Digital signature presence flag.
    int bindCount;///<Counter of successful bindings to devices.

public:
/**
 * @brief Default constructor.
 */
    Driver();

/**
 * @brief Constructor with parameters.
 * @param name Driver name.
 * @param deviceName Device name.
 * @param isSigned Signature presence.
 */
    Driver(const std::string& name,const std::string& deviceName,bool isSigned);

/**
 * @brief Binds the driver to a component.
 * @param part Pointer to the component.
 * @exception DriverNotFoundException if the driver does not match this device.
 */
    void bind(Component* part);

/**
 * @brief Loads the driver into the system.
 * @exception BootFailureException if the driver does not have a digital signature.
 */
    void load();
};