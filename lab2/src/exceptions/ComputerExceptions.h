#pragma once
#include <stdexcept>
#include <string>

class ComputerException:public std::runtime_error{
public:
    explicit ComputerException(const std::string& msg):std::runtime_error(msg){}
};

class IncompatibleSocketException:public ComputerException{
public:
    explicit IncompatibleSocketException(const std::string& msg):ComputerException(msg){}
};

class InsufficientPowerException:public ComputerException{
public:
    explicit InsufficientPowerException(const std::string& msg):ComputerException(msg){}
};

class OverheatingException:public ComputerException{
public:
    explicit OverheatingException(const std::string& msg):ComputerException(msg){}
};

class DriverNotFoundException:public ComputerException{
public:
    explicit DriverNotFoundException(const std::string& msg):ComputerException(msg){}
};

class MemoryOverflowException:public ComputerException{
public:
    explicit MemoryOverflowException(const std::string& msg):ComputerException(msg){}
};

class DiskFullException:public ComputerException{
public:
    explicit DiskFullException(const std::string& msg):ComputerException(msg){}
};

class NetworkDisconnectedException:public ComputerException{
public:
    explicit NetworkDisconnectedException(const std::string& msg):ComputerException(msg){}
};

class InvalidConfigurationException:public ComputerException{
public:
    explicit InvalidConfigurationException(const std::string& msg):ComputerException(msg){}
};

class UnauthorizedAccessException:public ComputerException{
public:
    explicit UnauthorizedAccessException(const std::string& msg):ComputerException(msg){}
};

class BootFailureException:public ComputerException{
public:
    explicit BootFailureException(const std::string& msg):ComputerException(msg){}
};

class PeripheralNotRespondingException:public ComputerException{
public:
    explicit PeripheralNotRespondingException(const std::string& msg):ComputerException(msg){}
};