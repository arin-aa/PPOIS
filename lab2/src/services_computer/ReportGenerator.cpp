#include "ReportGenerator.h"
#include "Computer.h"
#include "File.h"

const char* const DEFAULT_REPORT_FORMAT="txt";
const char* const DEFAULT_REPORT_AUTHOR="unknown";

ReportGenerator::ReportGenerator():format(DEFAULT_REPORT_FORMAT),author(DEFAULT_REPORT_AUTHOR){}

ReportGenerator::ReportGenerator(const std::string& format,const std::string& author):format(format),author(author){}

std::string ReportGenerator::generateReport(Computer* computer){
    if(!computer){
        return "";
    }
    std::string report="Report by "+author+"\n";
    report+="Format: "+format+"\n";
    report+="Host: "+computer->hostname+"\n";
    report+="Power draw: "+std::to_string(computer->totalPowerDraw())+"W\n";
    return report;
}

bool ReportGenerator::saveToFile(const std::string& content,File* file){
    if(!file || content.empty()){
        return false;
    }
    return file->writeText(content);
}
