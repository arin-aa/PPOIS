/**
 * @file Process.h
 * @brief Объявление класса Process.
 */
#pragma once
#include <string>

class Application;

/**
 * @class Process
 * @brief Класс, представляющий запущенный процесс приложения.
 */
class Process{
private:
    int ramUsageMb;///<Объем используемой оперативной памяти.
    std::string state;///<Текущее состояние процесса ("new", "running", "stopped").
    Application* app;///<Указатель на запущенное приложение.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Process();

/**
 * @brief Конструктор с указанием приложения.
 * @param app Указатель на приложение.
 */
    explicit Process(Application* app);


/**
 * @brief Запускает процесс.
 * @param freeRamMb Доступная оперативная память.
 * @return Объем памяти, занятый процессом.
 * @exception MemoryOverflowException если приложению не хватает памяти.
 */
    int start(int freeRamMb);

/**
 * @brief Завершает процесс.
 * @return Освобожденный объем оперативной памяти.
 */
    int terminate();
};
