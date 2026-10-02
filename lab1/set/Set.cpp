/**
 * @file Set.cpp
 * @brief Реализация методов класса CantorSet.
 */
#include "Set.h"                    
#include <algorithm> 
#include <cctype>
#include <stdexcept>

bool CantorSet::isEmpty()const{
    return element.empty() && subset.empty();
}

bool CantorSet::addElement(const std::string& value){
    if(value.empty()){
        return false;
    }
    return element.insert(value).second;
}

bool CantorSet::operator<(const CantorSet& other)const{
    if(element!=other.element){
        return element<other.element;
    }
    if(subset.size()!=other.subset.size()){
        return subset.size()<other.subset.size();
    }
    for(std::size_t i=0;i<subset.size();i++){
        if(*subset[i]<*other.subset[i]){
            return true;
        }
        if(*other.subset[i]<*subset[i]){
            return false;
        }
    }
    return false;
}

void CantorSet::sortSubset(){
    std::sort(subset.begin(),subset.end(),[](const auto& elem1,const auto& elem2){
        return *elem1<*elem2;
    }
    );
}

bool CantorSet::operator!=(const CantorSet& other)const{
    return !(*this==other);
}

bool CantorSet::operator==(const CantorSet& other)const{
    if(element!=other.element){
        return false;
    }
    if(subset.size()!=other.subset.size()){
        return false;
    }
    for(std::size_t i=0;i<subset.size();i++){
        if((*subset[i])!=(*other.subset[i])){
            return false;
        }
    }
    return true;
}

bool CantorSet::addSubset(const CantorSet& sub){
    for(const auto& subset_: subset){
        if((*subset_)==sub){
            return false;
        }
    }
    subset.push_back(std::make_shared<CantorSet>(sub));
    sortSubset();
    return true;
}

bool CantorSet::operator[](const std::string& value)const{
    return element.count(value)>0;
}

bool CantorSet::operator[](const CantorSet& sub)const{
    for(const auto& subset_: subset){
        if(*subset_==sub){
            return true;
        }
    }
    return false;
}

bool CantorSet::delElement(const std::string& value){
    return element.erase(value)>0;
}

bool CantorSet::delSubset(const CantorSet& del){
    for(auto sub=subset.begin();sub!=subset.end();sub++){
        if(**sub==del){
            subset.erase(sub);
            return true;
        }
    }
    return false;
}

std::size_t CantorSet::power()const{
    return element.size()+subset.size();
}

CantorSet& CantorSet::operator+=(const CantorSet& other){
    if(this == &other){
        return *this;
    } 
    element.insert(other.element.begin(),other.element.end());
    subset.insert(subset.end(),other.subset.begin(),other.subset.end());
    sortSubset();
    subset.erase(std::unique(subset.begin(),subset.end(),[](const auto& sub1,const auto& sub2){return *sub1==*sub2;}),subset.end());
    return *this;
}

CantorSet CantorSet::operator+(const CantorSet& other)const{
    CantorSet result=*this;
    result+=other;
    return result;
}

CantorSet& CantorSet::operator*=(const CantorSet& other){
    if(this == &other){
        return *this;
    }
    std::set<std::string> newElem;
    for(const auto& elem: element){
        if(other[elem]){
            newElem.insert(elem);
        }
    }
    element=std::move(newElem);

    std::vector<std::shared_ptr<CantorSet>> newSub;
    for(const auto& sub: subset){
        if(other[*sub]){
            newSub.push_back(sub);
        }
    }
    subset=std::move(newSub);
    return *this;
}

CantorSet CantorSet::operator*(const CantorSet& other)const{
    CantorSet result=*this;
    result*=other;
    return result;
}

CantorSet& CantorSet::operator-=(const CantorSet& other){
    if(this == &other){
        element.clear();
        subset.clear();
        return *this;
    }
    for(const auto& elem: other.element){
        element.erase(elem);
    }
    std::vector<std::shared_ptr<CantorSet>> newSubset;
    for(const auto& sub: subset){
        if(!other[*sub]){
            newSubset.push_back(sub);
        }
    }
    subset=std::move(newSubset);
    return *this;
}

CantorSet CantorSet::operator-(const CantorSet& other)const{
    CantorSet result=*this;
    result-=other;
    return result;
}

CantorSet CantorSet::bulean()const{
    CantorSet bulSet;
    bulSet.subset.push_back(std::make_shared<CantorSet>());
    for(const auto& elem: element){
        std::size_t n=bulSet.subset.size();
        for(std::size_t i=0;i<n;i++){
            auto newSub=std::make_shared<CantorSet>(*bulSet.subset[i]);
            newSub->addElement(elem);
            bulSet.subset.push_back(newSub);
        }
    }
    for(const auto& sub: subset){
        std::size_t m=bulSet.subset.size();
        for(std::size_t j=0;j<m;j++){
            auto newSub_=std::make_shared<CantorSet>(*bulSet.subset[j]);
            newSub_->addSubset(*sub);
            bulSet.subset.push_back(newSub_);
        }
    }
    bulSet.sortSubset();
    return bulSet;
}

std::ostream& operator<<(std::ostream& output,const CantorSet& symbol){
    output<<"{";
    bool first=true;
    for(const auto& elem: symbol.element){
        if(!first){
            output<<", ";
        }
        output<<elem;
        first=false;
    }
    for(const auto& sub: symbol.subset){
        if(!first){
            output<<", ";
        }
        output<<*sub;
        first=false;
    }
    output<<"}";
    return output;
}

void CantorSet::skipSpace(const std::string& symbol,std::size_t& pos){
    while(pos<symbol.size() && std::isspace(static_cast<unsigned char>(symbol[pos]))){
        ++pos;
    }
}

CantorSet CantorSet::parseSet(const std::string& symbol,std::size_t& pos){
    skipSpace(symbol,pos);
    if(pos>=symbol.size() || symbol[pos]!='{'){
        throw std::runtime_error("Ожидалась открывающая фигурная скобка.");
    }
    ++pos;
    CantorSet result;
    skipSpace(symbol,pos);
    if(pos<symbol.size() && symbol[pos]=='}'){
        ++pos;
        return result;
    }
    while(true){
        skipSpace(symbol,pos);
        if (pos>=symbol.size()) {
            throw std::runtime_error("Незакрытая фигурная скобка.");
        }
        if(symbol[pos]=='{'){
            CantorSet sub=parseSet(symbol,pos);
            result.addSubset(sub);
        }
        else if(std::isalnum(static_cast<unsigned char>(symbol[pos]))){
            std::size_t start=pos;
            while(pos<symbol.size() && std::isalnum(static_cast<unsigned char>(symbol[pos]))){
                ++pos;
            }
            result.addElement(symbol.substr(start,pos-start));
        }
        else{
            throw std::runtime_error("Недопустимый символ.");
        }
        skipSpace(symbol,pos);
        if(pos>=symbol.size()){
            throw std::runtime_error("Незакрытая фигурная скобка.");
        }
        if(symbol[pos]==','){
            ++pos;
            continue;
        }
        if(symbol[pos]=='}'){
            ++pos;
            return result;
        }
        throw std::runtime_error("Ожидалась ',' или '}'.");
    }
}

CantorSet CantorSet::fromString(const std::string& set){
    std::size_t n=0;
    CantorSet res=parseSet(set,n);
    skipSpace(set,n);
    if(n!=set.size()){
        throw std::runtime_error("Мусор после закрытия множества.");
    }
    return res;
}

std::istream& operator>>(std::istream& input, CantorSet& symbol) {
    std::string line;
    if(!std::getline(input, line)){
        return input;
    }              
    symbol = CantorSet::fromString(line);       
    return input;
}


