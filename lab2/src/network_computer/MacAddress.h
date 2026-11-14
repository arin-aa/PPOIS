/**
 * @file MacAddress.h
 * @brief Declaration of the MacAddress class.
 */
#pragma once
#include <string>

/**
 * @class MacAddress
 * @brief Class representing a MAC address.
 * 
 * Stores the address value and the manufacturer name, allows checking 
 * the correctness of the MAC address notation.
 */
class MacAddress{
private:
    std::string value;///<String value of the MAC address.
    std::string vendor;///<Manufacturer name.

public:
/**
 * @brief Default constructor.
 */
    MacAddress();

/**
 * @brief Constructor with parameters.
 * @param value String value of the MAC address.
 * @param vendor Manufacturer.
 */
    MacAddress(const std::string& value,const std::string& vendor);

/**
 * @brief Checks the correctness of the MAC address.
 * 
 * Checks the string length (must be 17 characters) and the presence of 
 * ':' separators in the required positions.
 * @exception InvalidAddressException if the format is incorrect.
 */
    void verify();
};