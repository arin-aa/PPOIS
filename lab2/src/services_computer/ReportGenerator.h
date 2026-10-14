#pragma once
#include <string>

class Computer;
class File;

class ReportGenerator{
private:
    std::string format;
    std::string author;

public:
    ReportGenerator();
    ReportGenerator(const std::string& format,const std::string& author);

    std::string generateReport(Computer* computer);
    bool saveToFile(const std::string& content,File* file);
};