#include "SearchService.h"
#include "Album.h"
#include "Artist.h"
#include "ContentCatalog.h"
#include "MediaLibrary.h"
#include "SearchQuery.h"
#include "Track.h"

const size_t MAX_SUGGESTIONS=5;
const std::string TYPE_FILTER="type";
const std::string TRACK_TYPE="track";
const std::string ALBUM_TYPE="album";
const std::string ARTIST_TYPE="artist";

static bool isWanted(const std::string& filterType,const std::string& itemType){
    return filterType.empty() || filterType==itemType;
}

SearchService::SearchService(ContentCatalog* catalog):catalog(catalog){}

std::vector<Album*> SearchService::searchAlbums(const std::string& text) const{
    std::vector<Album*> albums;
    const MediaLibrary* library=catalog->getLibrary();
    const std::vector<Album*>& allAlbums=library->getAlbums();
    for(Album* album:allAlbums){
        const std::string& title=album->getTitle();
        if(title.find(text)!=std::string::npos){
            albums.push_back(album);
        }
    }
    return albums;
}

std::vector<Artist*> SearchService::searchArtists(const std::string& text) const{
    std::vector<Artist*> artists;
    const MediaLibrary* library=catalog->getLibrary();
    const std::vector<Artist*>& allArtists=library->getArtists();
    for(Artist* artist:allArtists){
        const std::string& name=artist->getName();
        if(name.find(text)!=std::string::npos){
            artists.push_back(artist);
        }
    }
    return artists;
}

SearchResult SearchService::search(const SearchQuery& query){
    std::vector<Track*> tracks;
    std::vector<Album*> albums;
    std::vector<Artist*> artists;
    if(query.isEmpty()) return SearchResult(tracks,albums,artists);
    std::string text=query.normalize();
    std::string type=query.getFilter(TYPE_FILTER);
    if(isWanted(type,TRACK_TYPE)){
        tracks=catalog->searchByTitle(text);
    }
    if(isWanted(type,ALBUM_TYPE)){
        albums=searchAlbums(text);
    }
    if(isWanted(type,ARTIST_TYPE)){
        artists=searchArtists(text);
    }
    lastQuery=text;
    return SearchResult(tracks,albums,artists);
}

std::vector<std::string> SearchService::suggest(const std::string& prefix) const{
    std::vector<std::string> titles;
    const MediaLibrary* library=catalog->getLibrary();
    const std::vector<Track*>& allTracks=library->getTracks();
    for(const Track* track:allTracks){
        if(titles.size()>=MAX_SUGGESTIONS){
            break;
        }
        const std::string& title=track->getTitle();
        if(title.compare(0,prefix.size(),prefix)==0){
            titles.push_back(title);
        }
    }
    return titles;
}