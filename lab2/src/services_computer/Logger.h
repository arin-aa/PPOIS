/**
 * @file Logger.h
 * @brief Declaration of the Logger class.
 */
#pragma once
#include <string>
#include <vector>

/**
 * @class Logger
 * @brief Class for logging.
 * 
 * Stores messages with level indication, limits the history size,
 * and allows outputting the last N entries.
 */
class Logger{
private:
    std::string level;///<Logging level.
    std::vector<std::string> entries;///<List of saved entries.
    int maxEntries;///<Maximum number of stored entries.
    int dropped;///<Number of evicted old entries.

public:
/**
 * @brief Default constructor.
 */
    Logger();

/**
 * @brief Constructor with parameters.
 * @param level Logging level.
 * @param maxEntries Maximum number of entries.
 */
    Logger(const std::string& level,int maxEntries);

/**
 * @brief Adds a new message to the log.
 * @param message Message text.
 */
    void log(const std::string& message);

/**
 * @brief Returns the last N entries as a single string separated by a delimiter.
 * @param count Number of requested entries.
 * @return String with the last entries.
 */
    std::string tail(int count);
};