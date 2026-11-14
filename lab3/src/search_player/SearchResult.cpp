#include "SearchResult.h"
#include "Album.h"
#include "Artist.h"
#include "Track.h"

SearchResult::SearchResult(const std::vector<Track*>& tracks,const std::vector<Album*>& albums,
                           const std::vector<Artist*>& artists):
    tracks(tracks),albums(albums),artists(artists){}

std::string SearchResult::getTopResult() const{
    if(!tracks.empty()){
        return tracks[0]->getTitle();
    }
    if(!albums.empty()){
        return albums[0]->getTitle();
    }
    return artists.empty()?"":artists[0]->getName();
}

int SearchResult::getTotalCount() const{
    return static_cast<int>(tracks.size()+albums.size()+artists.size());
}