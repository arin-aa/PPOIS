#include "Inventory.h"
#include "Component.h"
#include "ComputerExceptions.h"

Inventory::Inventory():warehouse(""),capacity(0),takenCount(0){}

Inventory::Inventory(const std::string& warehouse,int capacity):warehouse(warehouse),capacity(capacity),takenCount(0){}

int Inventory::addItem(Component* item){
    if(static_cast<int>(items.size())>=capacity){
        throw InventoryFullException(warehouse+" has no free shelves");
    }
    items.push_back(item);
    return static_cast<int>(items.size());
}

Component* Inventory::takeItem(const std::string& key){
    for(size_t index=0;index<items.size();index++){
        if(items[index]->isNamed(key)){
            Component* found=items[index];
            items.erase(items.begin()+index);
            takenCount++;
            return found;
        }
    }
    return nullptr;
}
