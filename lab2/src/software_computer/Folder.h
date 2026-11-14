/**
 * @file Folder.h
 * @brief Declaration of the Folder class.
 */
#pragma once
#include <vector>

class File;

/**
 * @class Folder
 * @brief Class of a folder containing files.
 */
class Folder{
private:
    int freeMb;///<Free space in the folder in MB.
    std::vector<File*> files;///<List of files in the folder.

public:
/**
 * @brief Default constructor.
 */
    Folder();

/**
 * @brief Constructor with free space specified.
 * @param freeMb Initial free space in MB.
 */
    explicit Folder(int freeMb);

/**
 * @brief Adds a file to the folder.
 * @param file Pointer to the file.
 * @exception DiskFullException if the file does not fit into the folder.
 */
    void addFile(File* file);

/**
 * @brief Counts the total number of pages in all files of the folder.
 * @return Total number of pages.
 */
    int totalPages();
};