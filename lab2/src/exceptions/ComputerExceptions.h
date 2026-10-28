/**
 * @file ComputerExceptions.h
 * @brief Иерархия пользовательских исключений для системы учета компьютерной техники.
 */
#pragma once
#include <stdexcept>
#include <string>

/**
 * @class ComputerException
 * @brief Базовый класс для всех исключений предметной области.
 * 
 * Наследуется от std::runtime_error, что позволяет перехватывать все
 * ошибки системы одним блоком catch (const ComputerException&).
 */
class ComputerException:public std::runtime_error{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit ComputerException(const std::string& message):std::runtime_error(message){}
};

/**
 * @class IncompatibleSocketException
 * @brief Исключение при несовместимости сокетов процессора и материнской платы.
 */
class IncompatibleSocketException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit IncompatibleSocketException(const std::string& message):ComputerException(message){}
};

/**
 * @class InsufficientPowerException
 * @brief Исключение при недостаточной мощности блока питания.
 */
class InsufficientPowerException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit InsufficientPowerException(const std::string& message):ComputerException(message){}
};

/**
 * @class OverheatingException
 * @brief Исключение при критическом перегреве компонента.
 */
class OverheatingException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit OverheatingException(const std::string& message):ComputerException(message){}
};

/**
 * @class DriverNotFoundException
 * @brief Исключение, если драйвер не подходит к указанному устройству.
 */
class DriverNotFoundException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit DriverNotFoundException(const std::string& message):ComputerException(message){}
};

/**
 * @class MemoryOverflowException
 * @brief Исключение при нехватке оперативной или видеопамяти.
 */
class MemoryOverflowException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit MemoryOverflowException(const std::string& message):ComputerException(message){}
};

/**
 * @class DiskFullException
 * @brief Исключение при переполнении дискового пространства.
 */
class DiskFullException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit DiskFullException(const std::string& message):ComputerException(message){}
};

/**
 * @class NetworkDisconnectedException
 * @brief Исключение при попытке передачи данных через отключенный сетевой интерфейс.
 */
class NetworkDisconnectedException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit NetworkDisconnectedException(const std::string& message):ComputerException(message){}
};

/**
 * @class InvalidConfigurationException
 * @brief Исключение при некорректной конфигурации.
 */
class InvalidConfigurationException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit InvalidConfigurationException(const std::string& message):ComputerException(message){}
};

/**
 * @class UnauthorizedAccessException
 * @brief Исключение при попытке несанкционированного доступа к компоненте.
 */
class UnauthorizedAccessException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit UnauthorizedAccessException(const std::string& message):ComputerException(message){}
};

/**
 * @class BootFailureException
 * @brief Исключение при невозможности загрузки системы или компонента.
 */
class BootFailureException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit BootFailureException(const std::string& message):ComputerException(message){}
};

/**
 * @class PeripheralNotRespondingException
 * @brief Исключение, если периферийное устройство не отвечает или отключено.
 */
class PeripheralNotRespondingException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit PeripheralNotRespondingException(const std::string& message):ComputerException(message){}
};

/**
 * @class InventoryFullException
 * @brief Исключение при попытке добавить предмет на переполненный склад.
 */
class InventoryFullException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit InventoryFullException(const std::string& message):ComputerException(message){}
};

/**
 * @class InvalidAddressException
 * @brief Исключение при некорректном формате IP- или MAC-адреса.
 */
class InvalidAddressException:public ComputerException{
public:
/**
 * @brief Конструктор с сообщением об ошибке.
 * @param message Текст ошибки.
 */
    explicit InvalidAddressException(const std::string& message):ComputerException(message){}
};
