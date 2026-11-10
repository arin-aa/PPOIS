/**
 * @file File.h
 * @brief Declaration of the File class.
 */
#pragma once
#include <string>

/**
 * @class File
 * @brief Class representing a file in the file system.
 */

class File{
private:
    std::string fileName;///<File name.
    int sizeMb;///<File size in MB.
    bool isReadOnly;///<Read-only mode flag.
    std::string content;///<Text content of the file.

public:
/**
 * @brief Default constructor.
 */
    File();

/**
 * @brief Constructor with parameters.
 * @param fileName File name.
 * @param sizeMb Size in MB.
 * @param isReadOnly Read-only flag.
 */
    File(const std::string& fileName,int sizeMb,bool isReadOnly);

/**
 * @brief Appends text to the end of the file.
 * @param text Text to append.
 * @exception UnauthorizedAccessException if the file is read-only.
 */
    void append(const std::string& text);

/**
 * @brief Calculates the number of pages in the file.
 * @return Number of pages (1 page = 500 characters).
 */
    int pageCount();

/**
 * @brief Checks whether the file fits into the given free space.
 * @param freeMb Available free space.
 * @return Remaining free space after placing the file.
 * @exception DiskFullException if the file does not fit.
 */
    int fitInto(int freeMb);
};