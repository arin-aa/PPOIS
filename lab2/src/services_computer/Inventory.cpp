#include "Inventory.h"
#include "Component.h"
#include "ComputerExceptions.h"

const int DEFAULT_INVENTORY_CAPACITY=100;

Inventory::Inventory():warehouseName(""),capacity(DEFAULT_INVENTORY_CAPACITY){}

Inventory::Inventory(const std::string& warehouseName,int capacity):warehouseName(warehouseName),capacity(capacity){}

bool Inventory::addItem(Component* item){
    if(!item){
        return false;
    }
    if(static_cast<int>(items.size())>=capacity){
        throw InventoryFullException("warehouse "+warehouseName+" is full");
    }
    items.push_back(item);
    return true;
}

Component* Inventory::takeItem(const std::string& name){
    for(auto position=items.begin(); position!=items.end(); ++position){
        Component* item=*position;
        if(item && item->name==name){
            items.erase(position);
            return item;
        }
    }
    return nullptr;
}

int Inventory::countByType(const std::string& type){
    int matches=0;
    for(Component* item:items){
        if(item && item->name.find(type)!=std::string::npos){
            matches++;
        }
    }
    return matches;
}

int Inventory::getItemCount(){
    return static_cast<int>(items.size());
}
