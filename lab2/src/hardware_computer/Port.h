/**
 * @file Port.h
 * @brief Объявление класса Port.
 */

#pragma once
#include <string>

class Cable;

/**
 * @class Port
 * @brief Класс порта ввода-вывода.
 */
class Port{
private:
    std::string type;///<Тип порта.
    int speedMbps;///<Пропускная способность порта.
    Cable* cable;///<Подключенный кабель.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Port();

/**
 * @brief Конструктор с параметрами.
 * @param type Тип порта.
 * @param speedMbps Скорость.
 */
    Port(const std::string& type,int speedMbps);

/**
 * @brief Подключает кабель к порту.
 * @param newCable Указатель на кабель.
 */
    void plug(Cable* newCable);

/**
 * @brief Вычисляет реальную пропускную способность.
 * @return Скорость в Мбит/с.
 * @exception PeripheralNotRespondingException если нет кабеля.
 */
    int throughput();
};
