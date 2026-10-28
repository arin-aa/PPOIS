/**
 * @file OperatingSystem.h
 * @brief Объявление класса OperatingSystem.
 */
#pragma once
#include <vector>
#include "Process.h"
#include "Software.h"

class Driver;

/**
 * @class OperatingSystem
 * @brief Класс операционной системы, наследуемый от Software.
 * 
 * Управляет загрузкой драйверов и жизненным циклом процессов.
 */
class OperatingSystem:public Software{
private:
    bool isBooted;///<Флаг, указывающий, запущена ли ОС.
    int nextPid;///<Следующий доступный идентификатор процесса.
    std::vector<Process> processes;///<Список запущенных процессов.
    std::vector<Driver*> drivers;///<Список установленных драйверов.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    OperatingSystem();

/**
 * @brief Конструктор с параметрами.
 * @param name Название ОС.
 * @param sizeMb Размер ОС в МБ.
 */
    OperatingSystem(const std::string& name,int sizeMb);

/**
 * @brief Загружает операционную систему.
 * @exception BootFailureException если ОС не установлена или содержит неподписанные драйверы.
 */
    void boot();

/**
 * @brief Добавляет драйвер в систему.
 * @param driver Указатель на драйвер.
 */
    void addDriver(Driver* driver);

/**
 * @brief Запускает новый процесс.
 * @param process Указатель на процесс.
 * @param freeRamMb Доступная оперативная память.
 * @return Идентификатор запущенного процесса.
 * @exception BootFailureException если ОС еще не загружена.
 */
    int startProcess(Process* process,int freeRamMb);

/**
 * @brief Завершает процесс по его идентификатору.
 * @param pid Идентификатор процесса.
 * @return Освобожденная память в МБ, или возвращает -1, если процесс не найден.
 */
    int killProcess(int pid);
};
