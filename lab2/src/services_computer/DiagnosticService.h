/**
 * @file DiagnosticService.h
 * @brief Declaration of the DiagnosticService class.
 */
#pragma once

class Logger;
class Computer;

/**
 * @class DiagnosticService
 * @brief Computer diagnostic service.
 * 
 * Checks the system state for power and disk space issues, 
 * logs them, and calculates an overall health score.
 */
class DiagnosticService{
private:
    int issuesFound;///<Total number of issues found.
    int lowReserveWatts;///<Low power reserve threshold.
    int lowDiskGb;///<Low free space threshold.
    Logger* logger;///<Pointer to the logger object.

public:
/**
 * @brief Default constructor.
 */
    DiagnosticService();

/**
 * @brief Constructor with parameters.
 * @param lowReserveWatts Power reserve threshold.
 * @param lowDiskGb Free space threshold.
 * @param logger Pointer to the logger.
 */
    DiagnosticService(int lowReserveWatts,int lowDiskGb,Logger* logger);

/**
 * @brief Scans the computer for issues.
 * @param computer Pointer to the computer being checked.
 * @return Total number of issues found so far.
 */
    int scan(Computer* computer);

/**
 * @brief Calculates the system health score.
 * @return Score from 0 to 100 (each issue reduces the score by 25 points).
 */ 
    int healthScore();
};