/**
 * @file Fan.h
 * @brief Объявление класса Fan.
 */
#pragma once
#include "Component.h"

/**
 * @class Fan
 * @brief Класс вентилятора.
 */
class Fan:public Component{
private:
    int rpm;///<Скорость вращения.
    int sizeMm;///<Размер вентилятора в мм.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Fan();

/**
 * @brief Конструктор с параметрами.
 * @param sizeMm Размер.
 * @param rpm Начальная скорость.
 */
    Fan(int sizeMm,int rpm);

/**
 * @brief Изменяет скорость вращения.
 * @param delta Прирост/уменьшение оборотов.
 * @return Итоговая скорость.
 */
    int accelerate(int delta);

/**
 * @brief Вычисляет воздушный поток.
 * @return Поток.
 */
    int airflow();
};
