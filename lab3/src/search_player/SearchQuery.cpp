#include "SearchQuery.h"
#include <cctype>

SearchQuery::SearchQuery(const std::string& text,const std::string& typeFilter):text(text),typeFilter(typeFilter){}

std::string SearchQuery::normalize() const{
    std::string normalized;
    bool wordPending=false;
    for(unsigned char symbol:text){
        if(std::isalnum(symbol)){
            if(wordPending && !normalized.empty()){
                normalized+=' ';
            }
            wordPending=false;
            normalized+=static_cast<char>(std::tolower(symbol));
        }else{
            wordPending=true;
        }
    }
    return normalized;
}

bool SearchQuery::isEmpty() const{
    return normalize().empty();
}

bool SearchQuery::wantsType(const std::string& itemType) const{
    return typeFilter.empty() || typeFilter==itemType;
}