#include "MediaLibrary.h"
#include "Album.h"
#include "Artist.h"
#include "Genre.h"
#include "Track.h"

MediaLibrary::MediaLibrary(const std::vector<Track*>& tracks,const std::vector<Album*>& albums,
                           const std::vector<Artist*>& artists,const std::vector<Genre*>& genres):
    tracks(tracks),albums(albums),artists(artists),genres(genres){}

bool MediaLibrary::addTrack(Track* track){
    if(findTrackById(track->getId())!=nullptr){
        return false;
    }
    tracks.push_back(track);
    return true;
}

Track* MediaLibrary::findTrackById(int trackId) const{
    for(Track* track:tracks){
        if(track->getId()==trackId){
            return track;
        }
    }
    return nullptr;
}

std::vector<Track*> MediaLibrary::findByGenre(int genreId) const{
    std::vector<Track*> found;
    for(Track* track:tracks){
        if(track->hasGenre(genreId)){
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

std::vector<Album*> MediaLibrary::findAlbumsByTitle(const std::string& text) const{
    std::vector<Album*> found;
    for(Album* album:albums){
        const std::string& title=album->getTitle();
        if(title.find(text)!=std::string::npos){
            found.push_back(album);
        }
    }
    return found;
}

std::vector<Artist*> MediaLibrary::findArtistsByName(const std::string& text) const{
    std::vector<Artist*> found;
    for(Artist* artist:artists){
        const std::string& name=artist->getName();
        if(name.find(text)!=std::string::npos){
            found.push_back(artist);
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