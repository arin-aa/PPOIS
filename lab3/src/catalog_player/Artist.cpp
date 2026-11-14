#include "Artist.h"
#include "Album.h"
#include "MediaLibrary.h"

Artist::Artist(int id,const std::string& name,const std::vector<int>& albumIds,const std::string& imageUrl):
    id(id),name(name),albumIds(albumIds),imageUrl(imageUrl){}

int Artist::getTrackCount(const MediaLibrary* library) const{
    int trackCount=0;
    for(const Album* album:library->getAlbums()){
        for(int albumId:albumIds){
            if(albumId==album->getId()){
                trackCount+=album->getTrackCount();
                break;
            }
        }
    }
    return trackCount;
}

bool Artist::hasAlbums() const{
    return !albumIds.empty();
}

const std::string& Artist::getName() const{
    return name;
}