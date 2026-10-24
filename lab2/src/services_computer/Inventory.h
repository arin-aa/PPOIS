#pragma once
#include <string>
#include <vector>

class Component;

class Inventory{
private:
    std::vector<Component*> items;
    std::string warehouseName;
    int capacity;

public:
    Inventory();
    Inventory(const std::string& warehouseName,int capacity);

    bool addItem(Component* item);
    Component* takeItem(const std::string& name);
    int countByType(const std::string& type);
    int getItemCount();
};
