#pragma once
#include <stdexcept>
#include <string>

class ComputerException:public std::runtime_error{
public:
    explicit ComputerException(const std::string& message):std::runtime_error(message){}
};

class IncompatibleSocketException:public ComputerException{
public:
    explicit IncompatibleSocketException(const std::string& message):ComputerException(message){}
};

class InsufficientPowerException:public ComputerException{
public:
    explicit InsufficientPowerException(const std::string& message):ComputerException(message){}
};

class OverheatingException:public ComputerException{
public:
    explicit OverheatingException(const std::string& message):ComputerException(message){}
};

class DriverNotFoundException:public ComputerException{
public:
    explicit DriverNotFoundException(const std::string& message):ComputerException(message){}
};

class MemoryOverflowException:public ComputerException{
public:
    explicit MemoryOverflowException(const std::string& message):ComputerException(message){}
};

class DiskFullException:public ComputerException{
public:
    explicit DiskFullException(const std::string& message):ComputerException(message){}
};

class NetworkDisconnectedException:public ComputerException{
public:
    explicit NetworkDisconnectedException(const std::string& message):ComputerException(message){}
};

class InvalidConfigurationException:public ComputerException{
public:
    explicit InvalidConfigurationException(const std::string& message):ComputerException(message){}
};

class UnauthorizedAccessException:public ComputerException{
public:
    explicit UnauthorizedAccessException(const std::string& message):ComputerException(message){}
};

class BootFailureException:public ComputerException{
public:
    explicit BootFailureException(const std::string& message):ComputerException(message){}
};

class PeripheralNotRespondingException:public ComputerException{
public:
    explicit PeripheralNotRespondingException(const std::string& message):ComputerException(message){}
};

class InventoryFullException:public ComputerException{
public:
    explicit InventoryFullException(const std::string& message):ComputerException(message){}
};

class InvalidAddressException:public ComputerException{
public:
    explicit InvalidAddressException(const std::string& message):ComputerException(message){}
};
