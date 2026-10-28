/**
 * @file RAM.h
 * @brief Объявление класса RAM.
 */
#pragma once
#include "Component.h"

/**
 * @class RAM
 * @brief Класс оперативной памяти.
 */
class RAM:public Component{
private:
    int capacityGb;///<Объем в ГБ.
    int usedGb;///<Сколько использовано ГБ.
    int speedMhz;///<Частота.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    RAM();

/**
 * @brief Конструктор с параметрами.
 * @param capacityGb Объем.
 * @param speedMhz Частота.
 */ 
    RAM(int capacityGb,int speedMhz);

/**
 * @brief Выделяет память под процесс.
 * @param gb Запрашиваемый объем.
 * @return Время выделения в мс.
 * @exception MemoryOverflowException если не хватает памяти.
 */    
    int allocate(int gb);

/**
 * @brief Возвращает свободный объем.
 * @return Свободно ГБ.
 */
    int freeGb();
};
