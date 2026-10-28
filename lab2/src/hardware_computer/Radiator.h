/**
 * @file Radiator.h
 * @brief Объявление класса Radiator.
 */
#pragma once
#include "Cooler.h"

/**
 * @class Radiator
 * @brief Класс радиатора для жидкостного охлаждения.
 */
class Radiator:public Cooler{
private:
    int radiatorLengthMm;///<Длина радиатора в мм.
    int coolantMl;///<Объем хладагента в мл.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Radiator();

/**
 * @brief Конструктор с параметрами.
 * @param radiatorLengthMm Длина.
 * @param maxTdpWatts Максимальный TDP.
 */
    Radiator(int radiatorLengthMm,int maxTdpWatts);

/**
 * @brief Доливает хладагент.
 * @param milliliters Объем для добавления.
 * @return Итоговый объем, не должен превышать вместимость.
 */
    int refill(int milliliters);
};
