/**
 * @file Printer.h
 * @brief Объявление класса Printer.
 */
#pragma once
#include "Peripheral.h"

class File;

/**
 * @class Printer
 * @brief Класс принтера, наследуемый от Peripheral.
 */
class Printer:public Peripheral{
private:
    int paperLevel;///<Текущее количество листов бумаги.
    int inkLevel;///<Текущий уровень чернил.
    int printedPages;///<Общее количество напечатанных страниц.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Printer();

/**
 * @brief Конструктор с указанием начального уровня бумаги и чернил.
 * @param paperLevel Количество листов.
 * @param inkLevel Уровень чернил.
 */
    Printer(int paperLevel,int inkLevel);

/**
 * @brief Печатает файл.
 * @param file Указатель на файл для печати.
 * @return Общее количество напечатанных страниц.
 * @exception PeripheralNotRespondingException если не хватает бумаги или чернил.
 */
    int print(File* file);

/**
 * @brief Загружает бумагу в принтер.
 * @param sheets Количество добавляемых листов.
 * @return Итоговое количество бумаги (не более 250 листов).
 */
    int loadPaper(int sheets);
};
