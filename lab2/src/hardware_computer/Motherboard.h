/**
 * @file Motherboard.h
 * @brief Объявление класса Motherboard.
 */
#pragma once
#include <string>
#include <vector>
#include "Component.h"

class CPU;
class RAM;

/**
 * @class Motherboard
 * @brief Класс материнской платы.
 */
class Motherboard:public Component{
private:
    std::string socket;///<Тип сокета.
    int ramSlots;///<Количество слотов ОЗУ.
    CPU* cpu;///<Установленный процессор.
    std::vector<RAM*> ramModules;///<Установленные модули ОЗУ.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Motherboard();

/**
 * @brief Конструктор с параметрами.
 * @param socket Сокет.
 * @param ramSlots Количество слотов.
 */
    Motherboard(const std::string& socket,int ramSlots);

/**
 * @brief Устанавливает процессор.
 * @param newCpu Указатель на процессор.
 */ 
    void installCpu(CPU* newCpu);

/**
 * @brief Устанавливает модуль оперативной памяти.
 * @param ram Указатель на модуль.
 * @exception InvalidConfigurationException если нет свободных слотов.
 */
    void installRam(RAM* ram);

/**
 * @brief Возвращает суммарный объем свободной ОЗУ.
 * @return Объем в ГБ.
 */ 
    int freeRamGb();
};
