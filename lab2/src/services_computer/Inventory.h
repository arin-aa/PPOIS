/**
 * @file Inventory.h
 * @brief Объявление класса Inventory.
 */
#pragma once
#include <string>
#include <vector>

class Component;

/**
 * @class Inventory
 * @brief Класс склада комплектующих.
 * 
 * Позволяет добавлять компоненты на склад  
 * и забирать их по имени или производителю.
 */
class Inventory{
private:
    std::string warehouse;///<Название склада.
    int capacity;///<Максимальная вместимость склада.
    int takenCount;///<Количество выданных со склада предметов.
    std::vector<Component*> items;///<Список хранимых компонентов.

public:
/**
 * @brief Конструктор по умолчанию.
 */
    Inventory();

/**
 * @brief Конструктор с параметрами.
 * @param warehouse Название склада.
 * @param capacity Вместимость.
 */
    Inventory(const std::string& warehouse,int capacity);

/**
 * @brief Добавляет компонент на склад.
 * @param item Указатель на компонент.
 * @return Текущее количество предметов на складе.
 * @exception InventoryFullException если склад переполнен.
 */
    int addItem(Component* item);

/**
 * @brief Забирает компонент со склада по ключу (имени или производителю).
 * @param key Искомое значение.
 * @return Указатель на найденный компонент или nullptr, если не найден.
 */
    Component* takeItem(const std::string& key);
};
