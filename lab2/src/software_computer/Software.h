/**
 * @file Software.h
 * @brief Declaration of the base class Software.
 */
#pragma once
#include <string>

/**
 * @class Software
 * @brief Base class for all software.
 * 
 * Contains common properties (name, size, installation status) 
 * and disk installation logic.
 */
class Software{
protected:
    std::string name;///<Software name.
    int sizeMb;///<Program size in megabytes.
    bool isInstalled;///<Flag indicating whether the program is installed.

public:
/**
 * @brief Default constructor.
 */
    Software();

/**
 * @brief Constructor with parameters.
 * @param name Program name.
 * @param sizeMb Program size in MB.
 */
    Software(const std::string& name,int sizeMb);

/**
 * @brief Virtual default destructor.
 */
    virtual ~Software()=default;

/**
 * @brief Installs the program to disk.
 * @param freeGb Available free space in gigabytes.
 * @return Number of gigabytes required for installation.
 * @exception DiskFullException if there is not enough free space.
 */
    int install(int freeGb);
};