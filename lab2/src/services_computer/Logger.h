/**
 * @file Logger.h
 * @brief Объявление класса Logger.
 */
#pragma once
#include <string>
#include <vector>

/**
 * @class Logger
 * @brief Класс для ведения логов.
 * 
 * Хранит сообщения с указанием уровня, ограничивает размер истории 
 * и позволяет выводить последние N записей.
 */
class Logger{
private:
    std::string level;///<Уровень логирования.
    std::vector<std::string> entries;///<Список сохраненных записей.
    int maxEntries;///<Максимальное количество хранимых записей.
    int dropped;///<Количество вытесненных старых записей.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Logger();

/**
 * @brief Конструктор с параметрами.
 * @param level Уровень логирования.
 * @param maxEntries Максимальное количество записей.
 */
    Logger(const std::string& level,int maxEntries);

/**
 * @brief Добавляет новое сообщение в лог.
 * @param message Текст сообщения.
 */
    void log(const std::string& message);

/**
 * @brief Возвращает последние N записей в виде одной строки через разделитель.
 * @param count Количество запрашиваемых записей.
 * @return Строка с последними записями.
 */
    std::string tail(int count);
};
