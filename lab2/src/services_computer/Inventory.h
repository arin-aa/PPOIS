/**
 * @file Inventory.h
 * @brief Declaration of the Inventory class.
 */
#pragma once
#include <string>
#include <vector>

class Component;

/**
 * @class Inventory
 * @brief Component warehouse class.
 * 
 * Allows adding components to the warehouse 
 * and taking them out by name or manufacturer.
 */
class Inventory{
private:
    std::string warehouse;///<Warehouse name.
    int capacity;///<Maximum warehouse capacity.
    int takenCount;///<Number of items issued from the warehouse.
    std::vector<Component*> items;///<List of stored components.

public:
/**
 * @brief Default constructor.
 */
    Inventory();

/**
 * @brief Constructor with parameters.
 * @param warehouse Warehouse name.
 * @param capacity Capacity.
 */
    Inventory(const std::string& warehouse,int capacity);

/**
 * @brief Adds a component to the warehouse.
 * @param item Pointer to the component.
 * @return Current number of items in the warehouse.
 * @exception InventoryFullException if the warehouse is full.
 */
    int addItem(Component* item);

/**
 * @brief Takes a component from the warehouse by key (name or manufacturer).
 * @param key The value to search for.
 * @return Pointer to the found component or nullptr if not found.
 */
    Component* takeItem(const std::string& key);
};