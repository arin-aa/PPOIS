#include "ReportGenerator.h"
#include "Computer.h"
#include "File.h"

ReportGenerator::ReportGenerator():format("txt"),author("unknown"){}

ReportGenerator::ReportGenerator(const std::string& format,const std::string& author):format(format),author(author){}

std::string ReportGenerator::generateReport(Computer* computer){
    if(!computer){
        return "";
    }
    std::string report="Report by "+author+"\n";
    report+="Format: "+format+"\n";
    return report;
}

bool ReportGenerator::saveToFile(const std::string& content,File* file){
    if(!file){
        return false;
    }
    if(content.empty()){
        return false;
    }
    return true;
}