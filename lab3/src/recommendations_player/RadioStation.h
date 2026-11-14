/**
 * @file RadioStation.h
 * @brief Declaration of the RadioStation class.
 */
#pragma once
#include <string>
#include <vector>

/**
 * @class RadioStation
 * @brief Internet radio station with a stream address.
 */
class RadioStation{
private:
    std::string name;///<Name of the station.
    std::string streamUrl;///<Address of the audio stream.

public:
/**
 * @brief Constructor with parameters.
 * @param name Name of the station.
 * @param streamUrl Address of the audio stream.
 */
    RadioStation(const std::string& name,const std::string& streamUrl);

/**
 * @brief Connects to the stream.
 * @return Address of the stream that is ready to be played.
 * @exception PlaybackException if the address is not an http or https address.
 */
    std::string tuneIn() const;

/**
 * @brief Guesses the genre of the station from its name.
 * @param genreNames Names of the known genres.
 * @return First genre name that is part of the station name, empty string if there is none.
 */
    std::string classifyGenre(const std::vector<std::string>& genreNames) const;
};