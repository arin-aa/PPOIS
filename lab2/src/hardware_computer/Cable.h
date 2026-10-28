/**
 * @file Cable.h
 * @brief Объявление класса Cable.
 */
#pragma once
#include <string>

/**
 * @class Cable
 * @brief Класс, представляющий соединительный кабель.
 */
class Cable{
private:
    std::string type;///<Тип кабеля
    double lengthMeters;///<Длина кабеля в метрах.
    int maxMbps;///<Максимальная пропускная способность.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Cable();

/**
 * @brief Конструктор с параметрами.
 * @param type Тип кабеля.
 * @param lengthMeters Длина.
 * @param maxMbps Максимальная скорость.
 */
    Cable(const std::string& type,double lengthMeters,int maxMbps);

/**
 * @brief Проверяет совместимость кабеля с портом.
 * @param portType Тип порта.
 * @exception InvalidConfigurationException если типы не совпадают.
 */ 
    void match(const std::string& portType);

/**
 * @brief Вычисляет реальную пропускную способность с учетом затухания.
 * @return Эффективная скорость в Мбит/с.
 */
    int effectiveMbps();
};
