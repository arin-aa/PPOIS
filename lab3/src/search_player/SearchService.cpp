#include "SearchService.h"
#include "Album.h"
#include "Artist.h"
#include "ContentCatalog.h"
#include "MediaLibrary.h"
#include "SearchQuery.h"
#include "Track.h"

const size_t MAX_SUGGESTIONS=5;
const std::string TRACK_TYPE="track";
const std::string ALBUM_TYPE="album";
const std::string ARTIST_TYPE="artist";

SearchService::SearchService(ContentCatalog* catalog):catalog(catalog){}

SearchResult SearchService::search(const SearchQuery& query){
    std::vector<Track*> tracks;
    std::vector<Album*> albums;
    std::vector<Artist*> artists;
    if(query.isEmpty()){
        return SearchResult(tracks,albums,artists);
    }
    const MediaLibrary* library=catalog->getLibrary();
    std::string text=query.normalize();
    if(query.wantsType(TRACK_TYPE)){
        tracks=catalog->searchByTitle(text);
    }
    if(query.wantsType(ALBUM_TYPE)){
        albums=library->findAlbumsByTitle(text);
    }
    if(query.wantsType(ARTIST_TYPE)){
        artists=library->findArtistsByName(text);
    }
    return SearchResult(tracks,albums,artists);
}

std::vector<std::string> SearchService::suggest(const std::string& prefix) const{
    std::vector<std::string> titles;
    const MediaLibrary* library=catalog->getLibrary();
    for(const Track* track:library->getTracks()){
        if(titles.size()>=MAX_SUGGESTIONS){
            break;
        }
        const std::string& title=track->getTitle();
        if(title.rfind(prefix,0)==0){
            titles.push_back(title);
        }
    }
    return titles;
}