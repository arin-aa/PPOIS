/**
 * @file NetworkInterface.h
 * @brief Declaration of the NetworkInterface class.
 */
#pragma once

class IpAddress;

/**
 * @class NetworkInterface
 * @brief Network interface (network card) class.
 * 
 * Manages the connection state, IP address binding, 
 * and data transmission.
 */
class NetworkInterface{
private:
    bool isUp;///<Interface activity flag.
    int speedMbps;///<Throughput.
    int bytesSent;///<Counter of sent bytes.
    IpAddress* ip;///<Pointer to the bound IP address.

public:
/**
 * @brief Default constructor.
 */
    NetworkInterface();

/**
 * @brief Constructor with speed specified.
 * @param speedMbps Speed in Mbps.
 */
    explicit NetworkInterface(int speedMbps);

/**
 * @brief Connects an IP address to the interface.
 * @param newIp Pointer to the IP address object.
 * @exception InvalidAddressException if the passed IP is invalid.
 */
    void connect(IpAddress* newIp);

/**
 * @brief Calculates the transmission time for a given number of bits.
 * @param bits Number of bits to transmit.
 * @return Transmission time in nanoseconds.
 * @exception NetworkDisconnectedException if the interface is down or there is no IP.
 */
    int transmitNs(int bits);
};