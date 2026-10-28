/**
 * @file ReportGenerator.h
 * @brief Объявление класса ReportGenerator.
 */
#pragma once
#include <string>

class Computer;
class File;

/**
 * @class ReportGenerator
 * @brief Генератор отчетов о состоянии компьютера.
 * 
 * Формирует строковое представление характеристик ПК и сохраняет его в файл.
 */
class ReportGenerator{
private:
    std::string format;///<Формат отчета.
    std::string author;///<Автор отчета.
    int reportsMade;///<Счетчик сгенерированных отчетов.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    ReportGenerator();

/**
 * @brief Конструктор с параметрами.
 * @param format Формат отчета.
 * @param author Автор.
 */
    ReportGenerator(const std::string& format,const std::string& author);

/**
 * @brief Генерирует текст отчета по данным компьютера.
 * @param computer Указатель на компьютер.
 * @return Строка с отчетом.
 */
    std::string generate(Computer* computer);

/**
 * @brief Сохраняет готовый отчет в файл.
 * @param text Текст отчета.
 * @param file Указатель на файл для записи.
 * @exception UnauthorizedAccessException если файл доступен только для чтения.
 */
    void save(const std::string& text,File* file);
};
