#include "Track.h"
#include <algorithm>
#include <cctype>
#include "AudioFile.h"

static std::string toLower(std::string text){
    std::transform(text.begin(),text.end(),text.begin(),[](unsigned char symbol){
        return static_cast<char>(std::tolower(symbol));
    });
    return text;
}


Track::Track(int id,const std::string& title,int artistId,int albumId,int durationMs,AudioFile* audioFile,
             const std::vector<int>& genreIds):
    id(id),title(title),artistId(artistId),albumId(albumId),durationMs(durationMs),audioFile(audioFile),genreIds(genreIds){}

bool Track::isPlayable() const{
    return audioFile!=nullptr && durationMs>0;
}

bool Track::matchesQuery(const std::string& query) const{
    if (query.empty()) {
        return false;
    }
    std::string lowerTitle = toLower(title);
    std::string lowerQuery = toLower(query);
    return lowerTitle.find(lowerQuery) != std::string::npos;
}

int Track::getId() const{
    return id;
}

const std::string& Track::getTitle() const{
    return title;
}

int Track::getArtistId() const{
    return artistId;
}

int Track::getDurationMs() const{
    return durationMs;
}

AudioFile* Track::getAudioFile() const{
    return audioFile;
}

const std::vector<int>& Track::getGenreIds() const{
    return genreIds;
}