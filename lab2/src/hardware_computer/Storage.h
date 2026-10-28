/**
 * @file Storage.h
 * @brief Объявление класса Storage.
 */
#pragma once
#include <string>
#include "Component.h"

/**
 * @class Storage
 * @brief Класс для всех накопителей.
 */
class Storage:public Component{
protected:
    int capacityGb;///<Объем в ГБ.
    int usedGb;///<Сколько ГБ занято.
    int writeCount;///<Количество операций записи.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Storage();

/**
 * @brief Конструктор с параметрами.
 * @param name Название накопителя.
 * @param capacityGb Объем.
 */
    Storage(const std::string& name,int capacityGb);

/**
 * @brief Записывает данные.
 * @param gb Объем.
 * @exception DiskFullException если места не хватает.
 */
    void write(int gb);

/**
 * @brief Стирает данные.
 * @param gb Объем для стирания.
 * @return Фактически стертый объем.
 */
    int erase(int gb);

/**
 * @brief Возвращает количество свободного место.
 * @return Свободно ГБ.
 */
    int freeSpace();

/**
* @brief Виртуальный метод расчета остатка жизни.
* @return Процент.
*/
    virtual int lifeLeft();
};
