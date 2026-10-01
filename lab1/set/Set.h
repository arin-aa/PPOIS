#ifndef SET_H
#define SET_H
#include <cstddef>
#include <iostream>
#include <vector>
#include <set> 
#include <memory>          
#include <string>                     


class CantorSet{
    private:
    std::set<std::string> element;
    std::vector<std::shared_ptr<CantorSet>> subset;
    void sortSubset();
    static void skipSpace(const std::string& symbol,std::size_t& pos);
    static CantorSet parseSet(const std::string& symbol,std::size_t& pos);

    public:
    bool isEmpty()const;
    bool addElement(const std::string& value);
    bool operator<(const CantorSet& other)const;
    bool operator!=(const CantorSet& other)const;
    bool operator==(const CantorSet& other)const;
    bool addSubset(const CantorSet& sub);
    bool operator[](const std::string& value)const;
    bool operator[](const CantorSet& set_)const;
    bool delElement(const std::string& value);
    bool delSubset(const CantorSet& sub);
    std::size_t power()const;
    CantorSet& operator+=(const CantorSet& other);
    CantorSet operator+(const CantorSet& other)const;
    CantorSet& operator*=(const CantorSet& other);
    CantorSet operator*(const CantorSet& other)const;
    CantorSet& operator-=(const CantorSet& other);
    CantorSet operator-(const CantorSet& other)const;
    CantorSet bulean()const;    
    friend std::ostream& operator<<(std::ostream& output,const CantorSet& symbol);
    friend std::istream& operator>>(std::istream& input,CantorSet& symbol);
    static CantorSet fromString(const std::string& text);
 };
#endif 