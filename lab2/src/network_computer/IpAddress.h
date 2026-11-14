/**
 * @file IpAddress.h
 * @brief Declaration of the IpAddress class.
 */
#pragma once
#include <string>

/**
 * @class IpAddress
 * @brief Class representing an IP address.
 * 
 * Stores the string representation of the address and the subnet mask,
 * allows checking the validity of the address and comparing subnets.
 */
class IpAddress{
private:
    std::string address;///<String representation of the IP address.
    int subnetMask;///<Subnet mask.

public:
/**
 * @brief Default constructor.
 */
    IpAddress();

/**
 * @brief Constructor with parameters.
 * @param address String representation of the IP.
 * @param subnetMask Subnet mask.
 */
    IpAddress(const std::string& address,int subnetMask);

/**
 * @brief Checks the validity of the IP address.
 * 
 * Parses the string, checking for the presence of 4 octets and their values.
 * @exception InvalidAddressException if the address has an invalid format.
 */ 
    void validate();

/**
 * @brief Checks whether another IP is in the same subnet.
 * @param other String representation of another IP.
 * @return true if the addresses are in the same subnet.
 * @exception InvalidAddressException if the current or passed address is invalid.
 */
    bool sameSubnet(const std::string& other);
};