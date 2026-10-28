/**
 * @file Laptop.h
 * @brief Объявление класса Laptop.
 */
#pragma once
#include "Computer.h"

class Battery;

/**
 * @class Laptop
 * @brief Производный класс, представляющий ноутбук.
 * 
 * Расширяет базовый класс Computer, добавляя экран, батарею и 
 * возможность работы от аккумулятора.
 */
class Laptop:public Computer{
private:
    int screenInches;///<Диагональ экрана в дюймах.
    int chargedMinutes;///<Количество минут, на которое заряжена батарея.
    Battery* battery;///<Указатель на объект батареи.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Laptop();

/**
 * @brief Конструктор с параметрами.
 * @param hostname Сетевое имя.
 * @param screenInches Диагональ экрана.
 * @param battery Указатель на батарею.
 */
    Laptop(const std::string& hostname,int screenInches,Battery* battery);

/**
 * @brief Подключает ноутбук к зарядке.
 * @param minutes Время зарядки в минутах.
 * @return Текущий процент заряда батареи.
 */
    int plugIn(int minutes);

/**
 * @brief Рассчитывает время автономной работы.
 * @return Время работы от батареи в минутах.
 */   
    int batteryMinutes();

/**
 * @brief Переопределенный метод расчета энергопотребления.
 * Учитывает потребление экрана и базовых компонентов.
 * @return Потребляемая мощность в ваттах.
 */    
    int powerDraw() override;
};
