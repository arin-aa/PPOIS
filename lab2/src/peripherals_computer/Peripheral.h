/**
 * @file Peripheral.h
 * @brief Declaration of the base class Peripheral.
 */
#pragma once
#include <string>

class Port;

/**
 * @class Peripheral
 * @brief Base class for all peripheral devices.
 * 
 * Stores common properties (name, connection status) and 
 * provides basic methods for working with ports.
 */
class Peripheral{
protected:
    std::string name;///<Name of the peripheral device.
    bool isConnected;///<Flag indicating whether the device is connected.
    Port* port;///<Pointer to the port to which the device is connected.

public:
/**
 * @brief Default constructor.
 */
    Peripheral();

/**
 * @brief Constructor with device name specified.
 * @param name Device name.
 */
    explicit Peripheral(const std::string& name);

/**
 * @brief Virtual default destructor.
 */
    virtual ~Peripheral()=default;

/**
 * @brief Connects the device to the specified port.
 * @param targetPort Pointer to the port.
 * @exception PeripheralNotRespondingException if the port does not respond.
 */
    void connectTo(Port* targetPort);

/**
 * @brief Checks the device response.
 * @return Response latency in nanoseconds.
 * @exception PeripheralNotRespondingException if the device is not connected or there is no signal.
 */
    int ping();
};