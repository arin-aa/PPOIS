#include "ReportGenerator.h"
#include "Computer.h"
#include "File.h"

ReportGenerator::ReportGenerator():format(""),author(""),reportsMade(0){}

ReportGenerator::ReportGenerator(const std::string& format,const std::string& author):format(format),author(author),reportsMade(0){}

std::string ReportGenerator::generate(Computer* computer){
    reportsMade++;
    return "["+format+" #"+std::to_string(reportsMade)+" by "+author+"] draw="+std::to_string(computer->powerDraw())+"W, reserve="+
        std::to_string(computer->powerReserve())+"W, free="+std::to_string(computer->freeStorageGb())+"GB";
}

void ReportGenerator::save(const std::string& text,File* file){
    file->append(text);
}
