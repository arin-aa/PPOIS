#include "Inventory.h"
#include "Component.h"

Inventory::Inventory():warehouseName(""),capacity(100){}

Inventory::Inventory(const std::string& warehouseName,int capacity):warehouseName(warehouseName),capacity(capacity){}

bool Inventory::addItem(Component* item){
    if(!item){
        return false;
    }
    if((int)items.size()>=capacity){
        return false;
    }
    items.push_back(item);
    return true;
}

Component* Inventory::takeItem(const std::string& name){
    for(auto it=items.begin();it!=items.end();++it){
        if(*it && (*it)->name==name){
            Component* found=*it;
            items.erase(it);
            return found;
        }
    }
    return nullptr;
}

int Inventory::countByType(const std::string& type){
    int count=0;
    for(Component* c:items){
        if(c && c->name.find(type)!=std::string::npos){
            count++;
        }
    }
    return count;
}