#include "FavoritesCollection.h"

FavoritesCollection::FavoritesCollection(const std::string& userId):userId(userId),updatedAt(0){}

bool FavoritesCollection::toggle(int trackId,long long now){
    bool wasFavorite=contains(trackId);
    updatedAt=now;
    if(!wasFavorite){
        trackIds.push_back(trackId);
        return true;
    }
    std::vector<int> remaining;
    for(int favoriteId:trackIds){
        if(favoriteId!=trackId){
            remaining.push_back(favoriteId);
        }
    }
    trackIds=remaining;
    return false;
}

bool FavoritesCollection::contains(int trackId) const{
    for(int favoriteId:trackIds){
        if(favoriteId==trackId){
            return true;
        }
    }
    return false;
}