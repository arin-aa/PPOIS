/**
 * @file Webcam.h
 * @brief Объявление класса Webcam.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Webcam
 * @brief Класс веб-камеры, наследуемый от Peripheral.
 */
class Webcam:public Peripheral{
private:
    int heightPx;///<Высота видео в пикселях.
    int fps;///<Частота кадров в секунду.
    int recordedSeconds;///<Общее время записи в секундах.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Webcam();

/**
 * @brief Конструктор с указанием параметров видео.
 * @param heightPx Высота кадра.
 * @param fps Частота кадров.
 */
    Webcam(int heightPx,int fps);

/**
 * @brief Записывает видео.
 * @param seconds Длительность записи.
 * @return Объем записанных данных в килобайтах.
 */
    int record(int seconds);
};
