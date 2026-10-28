/**
 * @file Workstation.h
 * @brief Объявление класса Workstation.
 */
#pragma once
#include <vector>
#include "Computer.h"

class GPU;

/**
 * @class Workstation
 * @brief Производный класс, представляющий рабочую станцию.
 * 
 * Расширяет базовый класс Computer, добавляя поддержку нескольких 
 * видеокарт и возможность выполнения задач по рендерингу.
 */
class Workstation:public Computer{
private:
    int renderJobs;///<Счетчик выполненных задач рендеринга.
    std::vector<GPU*> gpus;///<Вектор установленных видеокарт.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Workstation();

/**
 * @brief Конструктор с указанием имени.
 * @param hostname Сетевое имя рабочей станции.
 */
    explicit Workstation(const std::string& hostname);

/**
 * @brief Добавляет видеокарту в систему.
 * @param gpu Указатель на объект видеокарты.
 */
    void addGpu(GPU* gpu);

/**
 * @brief Выполняет задачу рендеринга.
 * Распределяет нагрузку между имеющимися видеокартами.
 * @param complexity Сложность сцены для рендеринга.
 * @return Время выполнения рендеринга в миллисекундах (берется по самой медленной карте).
 * @exception InvalidConfigurationException если в системе нет ни одной видеокарты.
 */
    double renderTask(int complexity);
};
