/**
 * @file Monitor.h
 * @brief Объявление класса Monitor.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Monitor
 * @brief Класс монитора, наследуемый от Peripheral.
 */
class Monitor:public Peripheral{
private:
    int widthPx;///<Ширина экрана в пикселях.
    int heightPx;///<Высота экрана в пикселях.
    int brightness; ///<Текущий уровень яркости.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Monitor();

/**
 * @brief Конструктор с указанием разрешения экрана.
 * @param widthPx Ширина в пикселях.
 * @param heightPx Высота в пикселях.
 */
    Monitor(int widthPx,int heightPx);

/**
 * @brief Изменяет уровень яркости.
 * @param delta Прирост или уменьшение яркости.
 * @return Итоговый уровень яркости в пределах от 0 до 100.
 */
    int adjustBrightness(int delta);

/**
 * @brief Вычисляет разрешение экрана в мегапикселях.
 * @return Количество мегапикселей.
 */
    double megapixels();
};
