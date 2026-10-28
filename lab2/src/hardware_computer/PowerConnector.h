/**
 * @file PowerConnector.h
 * @brief Объявление класса PowerConnector.
 */
#pragma once

/**
 * @class PowerConnector
 * @brief Класс разъема питания.
 */
class PowerConnector{
private:
    int pinCount;///<Количество пинов.
    bool isPlugged;///<Флаг подключения.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    PowerConnector();

/**
 * @brief Конструктор с указанием количества пинов.
 * @param pinCount Количество пинов.
 */
    explicit PowerConnector(int pinCount);

/**
 * @brief Подключает разъем.
 * @return Количество пинов.
 * @exception InvalidConfigurationException если уже подключен.
 */ 
    int attach();
};
