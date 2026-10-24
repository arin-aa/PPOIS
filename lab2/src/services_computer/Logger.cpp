#include "Logger.h"

const char* const DEFAULT_LOG_LEVEL="INFO";
const int DEFAULT_LOG_ENTRIES=100;

Logger::Logger():level(DEFAULT_LOG_LEVEL),maxEntries(DEFAULT_LOG_ENTRIES){}

Logger::Logger(const std::string& level,int maxEntries):level(level),maxEntries(maxEntries){}

void Logger::log(const std::string& message){
    if(message.empty()){
        return;
    }
    entries.push_back("["+level+"] "+message);
    if(static_cast<int>(entries.size())>maxEntries){
        entries.erase(entries.begin());
    }
}

std::vector<std::string> Logger::getLastEntries(int count){
    if(count<=0){
        return {};
    }
    int available=static_cast<int>(entries.size());
    int firstIndex=0;
    if(available>count){
        firstIndex=available-count;
    }
    return std::vector<std::string>(entries.begin()+firstIndex,entries.end());
}

void Logger::clear(){
    entries.clear();
}

int Logger::getEntryCount(){
    return static_cast<int>(entries.size());
}
