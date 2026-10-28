#include "Logger.h"

const char* const JOIN="; ";

Logger::Logger():level(""),maxEntries(1),dropped(0){}

Logger::Logger(const std::string& level,int maxEntries):level(level),maxEntries(maxEntries>0?maxEntries:1),dropped(0){}

void Logger::log(const std::string& message){
    if(static_cast<int>(entries.size())>=maxEntries){
        entries.erase(entries.begin());
        dropped++;
    }
    entries.push_back("["+level+"] "+message);
}

std::string Logger::tail(int count){
    int size=static_cast<int>(entries.size());
    int first=count<size?size-count:0;
    std::string joined;
    for(int index=first;index<size;index++){
        joined+=(index>first?JOIN:"")+entries[index];
    }
    return joined;
}
