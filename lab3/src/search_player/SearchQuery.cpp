#include "SearchQuery.h"
#include <cctype>

SearchQuery::SearchQuery(const std::string& text,const std::map<std::string,std::string>& filters):
    text(text),filters(filters){}

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

std::string SearchQuery::getFilter(const std::string& name) const{
    auto found=filters.find(name);
    return found==filters.end()?"":found->second;
}