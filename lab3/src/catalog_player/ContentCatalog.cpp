#include "ContentCatalog.h"
#include "MediaLibrary.h"
#include "SearchQuery.h"
#include "Track.h"

ContentCatalog::ContentCatalog(MediaLibrary* library):library(library){}

std::vector<Track*> ContentCatalog::searchByTitle(const std::string& query) const{
    std::vector<Track*> found;
    std::string normalizedQuery=SearchQuery(query).normalize();
    if(normalizedQuery.empty()){
        return found;
    }
    const std::vector<Track*>& tracks=library->getTracks();
    for(size_t position=0;position<normalizedTitles.size() && position<tracks.size();position++){
        if(normalizedTitles[position].find(normalizedQuery)!=std::string::npos){
            found.push_back(tracks[position]);
        }
    }
    return found;
}

int ContentCatalog::rebuildIndex(){
    normalizedTitles.clear();
    for(const Track* track:library->getTracks()){
        const std::string& title=track->getTitle();
        std::string normalized=SearchQuery(title).normalize();
        normalizedTitles.push_back(normalized);
    }
    return static_cast<int>(normalizedTitles.size());
}

MediaLibrary* ContentCatalog::getLibrary() const{
    return library;
}