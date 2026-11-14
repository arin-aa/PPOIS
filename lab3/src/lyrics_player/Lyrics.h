/**
 * @file Lyrics.h
 * @brief Declaration of the Lyrics class.
 */
#pragma once
#include <string>
#include <vector>
#include "TimedLyric.h"

/**
 * @class Lyrics
 * @brief Synchronized text of a song.
 */
class Lyrics{
private:
    int trackId;///<Identifier of the track the text belongs to.
    std::vector<TimedLyric> lines;///<Lines ordered by start moment.
    std::string source;///<Where the text came from.

public:
/**
 * @brief Constructor with parameters.
 * @param trackId Identifier of the track.
 * @param lines Lines of the text, their start moments must grow.
 * @param source Where the text came from.
 * @exception MetadataException if a line does not start later than the previous one.
 */
    Lyrics(int trackId,const std::vector<TimedLyric>& lines,const std::string& source);

/**
 * @brief Finds the line that is shown at a moment.
 * @param positionMs Playback position (ms).
 * @return Text of the line, empty string before the first line.
 */
    std::string getLineAt(int positionMs) const;
};