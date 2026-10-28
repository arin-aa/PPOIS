/**
 * @file Software.h
 * @brief Объявление базового класса Software.
 */
#pragma once
#include <string>

/**
 * @class Software
 * @brief Базовый класс для всего программного обеспечения.
 * 
 * Содержит общие свойства (название, размер, статус установки) 
 * и логику установки на диск.
 */
class Software{
protected:
    std::string name;///<Название программного обеспечения.
    int sizeMb;///<Размер программы в мегабайтах.
    bool isInstalled;///<Флаг, указывающий, установлена ли программа.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Software();

/**
 * @brief Конструктор с параметрами.
 * @param name Название программы.
 * @param sizeMb Размер программы в МБ.
 */
    Software(const std::string& name,int sizeMb);

/**
 * @brief Виртуальный деструктор по умолчанию.
 */
    virtual ~Software()=default;

/**
 * @brief Устанавливает программу на диск.
 * @param freeGb Доступное свободное место в гигабайтах.
 * @return Необходимое для установки количество гигабайт.
 * @exception DiskFullException если свободного места недостаточно.
 */
    int install(int freeGb);
};
