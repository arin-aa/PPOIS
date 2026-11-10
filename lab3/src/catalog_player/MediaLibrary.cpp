#include "MediaLibrary.h"
#include <algorithm>
#include "Album.h"
#include "Artist.h"
#include "Genre.h"
#include "Track.h"

MediaLibrary::MediaLibrary(const std::vector<Track*>& tracks,const std::vector<Album*>& albums,
                           const std::vector<Artist*>& artists,const std::vector<Genre*>& genres):
    tracks(tracks),albums(albums),artists(artists),genres(genres){}

bool MediaLibrary::addTrack(Track* track){
    for(const Track* existing:tracks){
        if(existing->getId()==track->getId()){
            return false;
        }
    }
    tracks.push_back(track);
    return true;
}

std::vector<Track*> MediaLibrary::findByGenre(int genreId) const{
    std::vector<Track*> found;
    for(Track* track:tracks){
        const std::vector<int>& genreIds=track->getGenreIds();
        if(std::find(genreIds.begin(),genreIds.end(),genreId)!=genreIds.end()){
            found.push_back(track);
        }
    }
    return found;
}

std::vector<Track*> MediaLibrary::findByTitle(const std::string& query) const{
    std::vector<Track*> found;
    for(Track* track:tracks){
        if(track->matchesQuery(query)){
            found.push_back(track);
        }
    }
    return found;
}

const std::vector<Track*>& MediaLibrary::getTracks() const{
    return tracks;
}

const std::vector<Album*>& MediaLibrary::getAlbums() const{
    return albums;
}

const std::vector<Artist*>& MediaLibrary::getArtists() const{
    return artists;
}

const std::vector<Genre*>& MediaLibrary::getGenres() const{
    return genres;
}