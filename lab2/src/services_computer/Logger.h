#pragma once
#include <string>
#include <vector>

class Logger{
private:
    std::string level;
    std::vector<std::string> entries;
    int maxEntries;

public:
    Logger();
    Logger(const std::string& level,int maxEntries);

    void log(const std::string& message);
    std::vector<std::string> getLastEntries(int count);
    void clear();
    int getEntryCount();
};
