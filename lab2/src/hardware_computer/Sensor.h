/**
 * @file Sensor.h
 * @brief Объявление класса Sensor.
 */
#pragma once

/**
 * @class Sensor
 * @brief Класс датчика.
 */
class Sensor{
private:
    double value;///<Текущее показание.
    double threshold;///<Пороговое значение.
    int readings;///<Количество замеров.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Sensor();

/**
 * @brief Конструктор с порогом.
 * @param threshold Пороговое значение.
 */
    explicit Sensor(double threshold);

/**
 * @brief Добавляет новое показание и вычисляет среднее.
 * @param reading Новое значение.
 */    
    void measure(double reading);

/**
 * @brief Вычисляет запас до порога.
 * @return Разница между порогом и текущим значением.
 */
    double margin();
};
