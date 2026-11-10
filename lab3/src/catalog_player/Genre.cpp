#include "Genre.h"

const char GENRE_SEPARATOR='/';

Genre::Genre(int id,const std::string& name):id(id),name(name){}

bool Genre::isSubgenreOf(const Genre& parent) const{
    std::string prefix=parent.name+GENRE_SEPARATOR;
    return name.compare(0,prefix.size(),prefix)==0;
}

int Genre::getId() const{
    return id;
}

const std::string& Genre::getName() const{
    return name;
}