#include "FavoritesCollection.h"
#include <algorithm>

FavoritesCollection::FavoritesCollection(const std::string& userId):userId(userId),updatedAt(0){}

bool FavoritesCollection::toggle(int trackId,long long now){
    auto found=std::find(trackIds.begin(),trackIds.end(),trackId);
    updatedAt=now;
    if(found!=trackIds.end()){
        trackIds.erase(found);
        return false;
    }
    trackIds.push_back(trackId);
    return true;
}

bool FavoritesCollection::contains(int trackId) const{
    return std::find(trackIds.begin(),trackIds.end(),trackId)!=trackIds.end();
}