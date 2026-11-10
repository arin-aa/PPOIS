/**
 * @file ComputerExceptions.h
 * @brief Hierarchy of custom exceptions for the computer hardware accounting system.
 */
#pragma once
#include <stdexcept>
#include <string>

/**
 * @class ComputerException
 * @brief Base class for all domain exceptions.
 * 
 * Inherits from std::runtime_error, which allows catching all
 * system errors with a single catch block (const ComputerException&).
 */
class ComputerException:public std::runtime_error{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit ComputerException(const std::string& message):std::runtime_error(message){}
};

/**
 * @class IncompatibleSocketException
 * @brief Exception for incompatibility between the processor and motherboard sockets.
 */
class IncompatibleSocketException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit IncompatibleSocketException(const std::string& message):ComputerException(message){}
};

/**
 * @class InsufficientPowerException
 * @brief Exception for insufficient power supply capacity.
 */
class InsufficientPowerException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit InsufficientPowerException(const std::string& message):ComputerException(message){}
};

/**
 * @class OverheatingException
 * @brief Exception for critical overheating of a component.
 */
class OverheatingException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit OverheatingException(const std::string& message):ComputerException(message){}
};

/**
 * @class DriverNotFoundException
 * @brief Exception if a driver does not match the specified device.
 */
class DriverNotFoundException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit DriverNotFoundException(const std::string& message):ComputerException(message){}
};

/**
 * @class MemoryOverflowException
 * @brief Exception for insufficient RAM or video memory.
 */
class MemoryOverflowException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit MemoryOverflowException(const std::string& message):ComputerException(message){}
};

/**
 * @class DiskFullException
 * @brief Exception for disk space exhaustion.
 */
class DiskFullException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit DiskFullException(const std::string& message):ComputerException(message){}
};

/**
 * @class NetworkDisconnectedException
 * @brief Exception when attempting to transfer data through a disconnected network interface.
 */
class NetworkDisconnectedException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit NetworkDisconnectedException(const std::string& message):ComputerException(message){}
};

/**
 * @class InvalidConfigurationException
 * @brief Exception for an invalid configuration.
 */
class InvalidConfigurationException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit InvalidConfigurationException(const std::string& message):ComputerException(message){}
};

/**
 * @class UnauthorizedAccessException
 * @brief Exception when attempting unauthorized access to a component.
 */
class UnauthorizedAccessException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit UnauthorizedAccessException(const std::string& message):ComputerException(message){}
};

/**
 * @class BootFailureException
 * @brief Exception when the system or a component fails to boot.
 */
class BootFailureException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit BootFailureException(const std::string& message):ComputerException(message){}
};

/**
 * @class PeripheralNotRespondingException
 * @brief Exception if a peripheral device is not responding or is disconnected.
 */
class PeripheralNotRespondingException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit PeripheralNotRespondingException(const std::string& message):ComputerException(message){}
};

/**
 * @class InventoryFullException
 * @brief Exception when attempting to add an item to a full warehouse.
 */
class InventoryFullException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit InventoryFullException(const std::string& message):ComputerException(message){}
};

/**
 * @class InvalidAddressException
 * @brief Exception for an invalid IP or MAC address format.
 */
class InvalidAddressException:public ComputerException{
public:
/**
 * @brief Constructor with an error message.
 * @param message Error text.
 */
    explicit InvalidAddressException(const std::string& message):ComputerException(message){}
};