/**
 * @file NVMe.h
 * @brief Объявление класса NVMe.
 */
#pragma once
#include "Storage.h"

/**
 * @class NVMe
 * @brief Класс накопителя стандарта.
 */
class NVMe : public Storage {
private:
    int pcieLanes;///<Количество линий PCIe.
    int queueDepth;///<Глубина очереди команд.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    NVMe();

/**
 * @brief Конструктор с параметрами.
 * @param capacityGb Объем.
 * @param pcieLanes Количество линий.
 * @param queueDepth Глубина очереди.
 */ 
    NVMe(int capacityGb, int pcieLanes, int queueDepth);

/**
* @brief Рассчитывает скорость чтения.
* @return Скорость в МБ/с.
*/
    int readSpeed();
};
