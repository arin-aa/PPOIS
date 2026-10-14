#include "Logger.h"

Logger::Logger():level("INFO"),maxEntries(100){}

Logger::Logger(const std::string& level,int maxEntries):level(level),maxEntries(maxEntries){}

void Logger::log(const std::string& msg){
    if(msg.empty()){
        return;
    }
    entries.push_back("["+level+"] "+msg);
    if((int)entries.size()>maxEntries){
        entries.erase(entries.begin());
    }
}

int Logger::getLastEntries(int n){
    if(n<=0 || n>(int)entries.size()){
        return 0;
    }
    return n;
}

void Logger::clear(){
    entries.clear();
}