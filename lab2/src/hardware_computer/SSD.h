/**
 * @file SSD.h
 * @brief Объявление класса SSD.
 */
#pragma once
#include "Storage.h"

/**
 * @class SSD
 * @brief Класс накопителя.
 */
class SSD:public Storage{
private:
    int enduranceWrites;///<Ресурс записи (циклы).
    int trimCount;///<Количество операций TRIM.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    SSD();

/**
 * @brief Конструктор с указанием объема.
 * @param capacityGb Объем.
 */
    explicit SSD(int capacityGb);

/**
 * @brief Выполняет команду TRIM.
 * @return Освобожденный объем в ГБ.
 */ 
    int trim();

/**
* @brief Рассчитывает остаток ресурса.
* @return Процент оставшейся жизни.
*/ 
    int lifeLeft() override;
};
