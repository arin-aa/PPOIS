/**
 * @file Printer.h
 * @brief Declaration of the Printer class.
 */
#pragma once
#include "Peripheral.h"

class File;

/**
 * @class Printer
 * @brief Printer class, inheriting from Peripheral.
 */
class Printer:public Peripheral{
private:
    int paperLevel;///<Current number of paper sheets.
    int inkLevel;///<Current ink level.
    int printedPages;///<Total number of printed pages.

public:
/**
 * @brief Default constructor.
 */
    Printer();

/**
 * @brief Constructor with initial paper and ink levels specified.
 * @param paperLevel Number of sheets.
 * @param inkLevel Ink level.
 */
    Printer(int paperLevel,int inkLevel);

/**
 * @brief Prints a file.
 * @param file Pointer to the file to print.
 * @return Total number of printed pages.
 * @exception PeripheralNotRespondingException if there is not enough paper or ink.
 */
    int print(File* file);

/**
 * @brief Loads paper into the printer.
 * @param sheets Number of sheets to add.
 * @return Resulting amount of paper (no more than 250 sheets).
 */
    int loadPaper(int sheets);
};