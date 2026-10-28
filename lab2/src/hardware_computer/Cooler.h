/**
 * @file Cooler.h
 * @brief Объявление класса Cooler.
 */
#pragma once
#include <string>
#include "Component.h"

/**
 * @class Cooler
 * @brief Класс для систем охлаждения.
 */
class Cooler:public Component{
protected:
    int maxTdpWatts;///< Максимальный отводимый теплопакет

public:
/**
 * @brief Конструктор по умолчанию.
 */ 
    Cooler();

/**
 * @brief Конструктор с параметрами.
 * @param name Название кулера.
 * @param maxTdpWatts Максимальный TDP.
 */
    Cooler(const std::string& name,int maxTdpWatts);

/**
 * @brief Вычисляет запас охлаждения.
 * @param tdp Текущий теплопакет процессора.
 * @return Разница между максимальным и текущим TDP.
 */
    int headroom(int tdp);
};
