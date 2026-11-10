/**
 * @file Server.h
 * @brief Declaration of the Server class.
 */
#pragma once
#include <vector>
#include "Computer.h"

class NetworkInterface;
class Packet;

/**
 * @class Server
 * @brief Derived class representing a server.
 * 
 * Extends the base class Computer by adding RAID support, 
 * network request handling, and rack unit accounting.
 */
class Server:public Computer{
private:
    int rackUnits;///<Number of rack units.
    std::string raidLevel;///<Current RAID level
    int requestsServed;///<Counter of successfully processed requests.
    std::vector<NetworkInterface*> nics;///<Vector of network interfaces (cards).

public:
/**
 * @brief Default constructor.
 */
    Server();

/**
 * @brief Constructor with parameters.
 * @param hostname Server network name.
 * @param rackUnits Number of occupied rack units.
 * @param firstNic Pointer to the first network card.
 */
    Server(const std::string& hostname,int rackUnits,NetworkInterface* firstNic);

/**
 * @brief Configures the RAID level.
 * @param level String with the RAID level.
 * @return Percentage of usable disk capacity for the given RAID level.
 * @exception InvalidConfigurationException if an unknown RAID level is passed.
 */
    int configureRaid(const std::string& level);

/**
 * @brief Handles an incoming network packet.
 * @param packet Pointer to the packet.
 * @return Packet processing time in nanoseconds.
 * @exception NetworkDisconnectedException if the server has no network cards.
 */
    int handleRequest(Packet* packet);

/**
 * @brief Overridden method for calculating power consumption.
 * Takes into account the power consumption of network cards and occupied rack units.
 * @return Power consumption in watts.
 */   
    int powerDraw() override;
};