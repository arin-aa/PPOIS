/**
 * @file PSU.h
 * @brief Объявление класса PSU.
 */
#pragma once
#include <string>
#include "Component.h"

/**
 * @class PSU
 * @brief Класс блока питания.
 */
class PSU:public Component{
private:
    int wattage;///<Мощность
    std::string certification;///<Сертификат

public:
/**
 * @brief Конструктор по умолчанию.
 */
    PSU();

/**
 * @brief Конструктор с параметрами.
 * @param wattage Мощность.
 * @param certification Сертификат.
 */
    PSU(int wattage,const std::string& certification);

/**
 * @brief Вычисляет резерв мощности.
 * @param loadWatts Текущая нагрузка.
 * @return Резерв.
 */
    int reserve(int loadWatts);

/**
 * @brief Вычисляет потребление из сети.
 * @param loadWatts Полезная нагрузка.
 * @return Потребление из розетки.
 */
    int wallDraw(int loadWatts);
};
