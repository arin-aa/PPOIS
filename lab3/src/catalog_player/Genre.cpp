#include "Genre.h"

const char GENRE_SEPARATOR='/';

Genre::Genre(int id,const std::string& name):id(id),name(name){}

bool Genre::isSubgenreOf(const Genre& parent) const{
    std::string prefix=parent.name+GENRE_SEPARATOR;
    return name.rfind(prefix,0)==0;
}