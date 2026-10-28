/**
 * @file Peripheral.h
 * @brief Объявление базового класса Peripheral.
 */
#pragma once
#include <string>

class Port;

/**
 * @class Peripheral
 * @brief Базовый класс для всех периферийных устройств.
 * 
 * Хранит общие свойства (название, статус подключения) и 
 * предоставляет базовые методы для работы с портами.
 */
class Peripheral{
protected:
    std::string name;///<Название периферийного устройства.
    bool isConnected;///<Флаг, указывающий, подключено ли устройство.
    Port* port;///<Указатель на порт, к которому подключено устройство.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Peripheral();

/**
 * @brief Конструктор с указанием имени устройства.
 * @param name Название устройства.
 */
    explicit Peripheral(const std::string& name);

/**
 * @brief Виртуальный деструктор по умолчанию default.
 */
    virtual ~Peripheral()=default;

/**
 * @brief Подключает устройство к заданному порту.
 * @param targetPort Указатель на порт.
 * @exception PeripheralNotRespondingException если порт не отвечает.
 */
    void connectTo(Port* targetPort);

/**
 * @brief Проверяет отклик устройства.
 * @return Задержка отклика в наносекундах.
 * @exception PeripheralNotRespondingException если устройство не подключено или нет сигнала.
 */
    int ping();
};
