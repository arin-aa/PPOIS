/**
 * @file ReportGenerator.h
 * @brief Declaration of the ReportGenerator class.
 */
#pragma once
#include <string>

class Computer;
class File;

/**
 * @class ReportGenerator
 * @brief Computer state report generator.
 * 
 * Generates a string representation of PC specifications and saves it to a file.
 */
class ReportGenerator{
private:
    std::string format;///<Report format.
    std::string author;///<Report author.
    int reportsMade;///<Counter of generated reports.

public:
/**
 * @brief Default constructor.
 */
    ReportGenerator();

/**
 * @brief Constructor with parameters.
 * @param format Report format.
 * @param author Author.
 */
    ReportGenerator(const std::string& format,const std::string& author);

/**
 * @brief Generates report text based on computer data.
 * @param computer Pointer to the computer.
 * @return String with the report.
 */
    std::string generate(Computer* computer);

/**
 * @brief Saves the finished report to a file.
 * @param text Report text.
 * @param file Pointer to the file for writing.
 * @exception UnauthorizedAccessException if the file is read-only.
 */
    void save(const std::string& text,File* file);
};