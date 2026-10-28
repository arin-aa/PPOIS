/**
 * @file Scanner.h
 * @brief Объявление класса Scanner.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Scanner
 * @brief Класс сканера, наследуемый от Peripheral.
 */
class Scanner:public Peripheral{
private:
    int resolutionDpi;///<Разрешение сканирования.
    int colorBits;///<Глубина цвета в битах.
    int pagesScanned;///<Общее количество отсканированных страниц.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Scanner();

/**
 * @brief Конструктор с указанием параметров сканирования.
 * @param resolutionDpi Разрешение.
 * @param colorBits Глубина цвета.
 */
    Scanner(int resolutionDpi,int colorBits);

/**
 * @brief Сканирует заданное количество страниц.
 * @param pages Количество страниц.
 * @return Объем полученных данных в килобайтах.
 */
    int scanPages(int pages);
};
