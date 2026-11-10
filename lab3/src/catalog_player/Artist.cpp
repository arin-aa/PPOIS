#include "Artist.h"
#include <algorithm>
#include "Album.h"
#include "MediaLibrary.h"

Artist::Artist(int id,const std::string& name,const std::vector<int>& albumIds,const std::string& imageUrl):
    id(id),name(name),albumIds(albumIds),imageUrl(imageUrl){}

int Artist::getTrackCount(const MediaLibrary* library) const{
    int trackCount=0;
    for(const Album* album:library->getAlbums()){
        if(std::find(albumIds.begin(),albumIds.end(),album->getId())!=albumIds.end()){
            trackCount+=album->getTrackCount();
        }
    }
    return trackCount;
}

bool Artist::hasAlbums() const{
    return !albumIds.empty();
}

int Artist::getId() const{
    return id;
}

const std::string& Artist::getName() const{
    return name;
}