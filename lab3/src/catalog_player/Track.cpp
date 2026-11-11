#include "Track.h"
#include "AudioFile.h"
#include "SearchQuery.h"

Track::Track(int id,const std::string& title,int artistId,int albumId,int durationMs,AudioFile* audioFile,
             const std::vector<int>& genreIds):
    id(id),title(title),artistId(artistId),albumId(albumId),durationMs(durationMs),audioFile(audioFile),genreIds(genreIds){}

bool Track::isPlayable() const{
    return audioFile!=nullptr && durationMs>0;
}

bool Track::matchesQuery(const std::string& query) const{
    std::string normalizedQuery=SearchQuery(query).normalize();
    if(normalizedQuery.empty()){
        return false;
    }
    std::string normalizedTitle=SearchQuery(title).normalize();
    return normalizedTitle.find(normalizedQuery)!=std::string::npos;
}

bool Track::hasGenre(int genreId) const{
    for(int trackGenreId:genreIds){
        if(trackGenreId==genreId){
            return true;
        }
    }
    return false;
}

bool Track::hasAnyGenre(const std::vector<int>& otherGenreIds) const{
    for(int genreId:otherGenreIds){
        if(hasGenre(genreId)){
            return true;
        }
    }
    return false;
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