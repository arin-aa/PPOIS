/**
 * @file HDD.h
 * @brief Объявление класса HDD.
 */

#pragma once
#include "Storage.h"

/**
 * @class HDD
 * @brief Класс жесткого диска.
 */
class HDD:public Storage{
private:
    int rpm;///<Скорость шпинделя
    int badSectors;///<Количество блоков
    int fragmentation;///<Уровень фрагментации

public:
/**
 * @brief Конструктор по умолчанию.
 */
    HDD();

/**
 * @brief Конструктор с параметрами.
 * @param capacityGb Объем.
 * @param rpm Скорость.
 * @param fragmentation Фрагментация.
 */
    HDD(int capacityGb,int rpm,int fragmentation);

/**
 * @brief Выполняет дефрагментацию диска.
 * @return Затраченное время в минутах.
 */
    int defragment();

/**
 * @brief Рассчитывает остаток жизни диска.
 * @return Процент оставшегося ресурса.
 */
    int lifeLeft() override;
};
