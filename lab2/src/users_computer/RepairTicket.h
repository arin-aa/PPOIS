/**
 * @file RepairTicket.h
 * @brief Declaration of the RepairTicket class.
 */
#pragma once
#include <string>

class Computer;
class Technician;

/**
 * @class RepairTicket
 * @brief Repair ticket class.
 * 
 * Tracks the ticket lifecycle: from creation to technician assignment 
 * and closure with final cost calculation.
 */
class RepairTicket{
private:
    std::string description;///<Problem description.
    std::string status;///<Current status ("open", "assigned", "closed").
    int hoursSpent;///<Number of hours spent.
    Computer* computer;///<Pointer to the computer being repaired.
    Technician* technician;///<Pointer to the assigned technician.

public:
/**
 * @brief Default constructor.
 */
    RepairTicket();

/**
 * @brief Constructor with parameters.
 * @param description Problem description.
 * @param computer Pointer to the computer.
 */
    RepairTicket(const std::string& description,Computer* computer);

/**
 * @brief Assigns a technician to the ticket.
 * @param worker Pointer to the technician.
 * @exception InvalidConfigurationException if the ticket is already assigned or closed.
 */
    void assign(Technician* worker);

/**
 * @brief Performs computer diagnostics.
 * @return Remaining power supply reserve.
 */
    int diagnose();

/**
 * @brief Closes the ticket and calculates the cost.
 * @param hours Number of hours spent.
 * @return Total repair cost.
 * @exception UnauthorizedAccessException if no technician is assigned to the ticket.
 */
    int close(int hours);
};