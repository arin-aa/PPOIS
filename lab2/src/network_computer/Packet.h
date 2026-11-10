/**
 * @file Packet.h
 * @brief Declaration of the Packet class.
 */
#pragma once
#include <string>

class IpAddress;

/**
 * @class Packet
 * @brief Network packet class.
 * 
 * Contains information about the sender, recipient, packet size, 
 * and time to live (TTL).
 */
class Packet{
private:
    IpAddress* source;///<Pointer to the sender's IP address.
    std::string destination;///<Recipient's IP address.
    int sizeBytes;///<Packet size in bytes.
    int ttl;///<Packet time to live.

public:
/**
 * @brief Default constructor.
 */
    Packet();

/**
 * @brief Constructor with parameters.
 * @param source Pointer to the sender's IP.
 * @param destination Recipient's IP.
 * @param sizeBytes Size in bytes.
 * @param ttl Time to live.
 */
    Packet(IpAddress* source,const std::string& destination,int sizeBytes,int ttl);

/**
 * @brief Forwards the packet through the network, i.e., decrements the TTL.
 * @return Packet size in bits.
 * @exception NetworkDisconnectedException if the TTL has expired.
 */
    int forward();

/**
 * @brief Checks whether the recipient is in the local subnet.
 * @return true if the sender and recipient are in the same subnet.
 */
    bool isLocal();
};