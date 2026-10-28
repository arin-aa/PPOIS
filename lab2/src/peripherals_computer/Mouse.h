/**
 * @file Mouse.h
 * @brief Объявление класса Mouse.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Mouse
 * @brief Класс компьютерной мыши, наследуемый от Peripheral.
 */
class Mouse:public Peripheral{
private:
    int dpi;///<Текущая чувствительность мыши.
    int clicks;///<Счетчик кликов.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Mouse();

/**
 * @brief Конструктор с указанием чувствительности.
 * @param dpi Начальное значение DPI.
 */
    explicit Mouse(int dpi);
     
/** 
 * @brief Изменяет чувствительность мыши.
 * @param newDpi Новое значение DPI.
 * @return Установленное значение DPI.
 * @exception InvalidConfigurationException если DPI вне допустимого диапазона.
 */
    int changeDpi(int newDpi);

/**
 * @brief Имитирует клик мышью.
 * @return Общее количество кликов за все время.
 */
    int click();
};
