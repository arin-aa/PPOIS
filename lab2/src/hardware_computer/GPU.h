/**
 * @file GPU.h
 * @brief Объявление класса GPU.
 */
#pragma once
#include "Component.h"

/**
 * @class GPU
 * @brief Класс видеокарты.
 */
class GPU:public Component{
private:
    int vramGb;///<Объем видеопамяти в ГБ.
    int coreClockMhz;///<Частота ядра в МГц.
    int framesRendered;///<Количество отрендеренных кадров.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    GPU();

/**
 * @brief Конструктор с параметрами.
 * @param vramGb Объем памяти.
 * @param coreClockMhz Частота.
 */ 
    GPU(int vramGb,int coreClockMhz);

/**
 * @brief Рассчитывает время рендеринга сцены.
 * @param complexity Сложность сцены.
 * @return Время рендеринга в мс.
 * @exception MemoryOverflowException если сцена не влезает в VRAM.
 */
    double renderTime(int complexity);
};
