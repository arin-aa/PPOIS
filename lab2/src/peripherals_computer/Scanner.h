/**
 * @file Scanner.h
 * @brief Declaration of the Scanner class.
 */
#pragma once
#include "Peripheral.h"

/**
 * @class Scanner
 * @brief Scanner class, inheriting from Peripheral.
 */
class Scanner:public Peripheral{
private:
    int resolutionDpi;///<Scanning resolution.
    int colorBits;///<Color depth in bits.
    int pagesScanned;///<Total number of scanned pages.

public:
/**
 * @brief Default constructor.
 */
    Scanner();

/**
 * @brief Constructor with scanning parameters specified.
 * @param resolutionDpi Resolution.
 * @param colorBits Color depth.
 */
    Scanner(int resolutionDpi,int colorBits);

/**
 * @brief Scans the specified number of pages.
 * @param pages Number of pages.
 * @return Amount of received data in kilobytes.
 */
    int scanPages(int pages);
};