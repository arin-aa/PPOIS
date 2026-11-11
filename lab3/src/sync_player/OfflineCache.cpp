#include "OfflineCache.h"
#include "MusicPlayerExceptions.h"

const int NOT_CACHED=-1;

OfflineCache::OfflineCache(long long maxSize,long long ttl):maxSize(maxSize),ttl(ttl){}

int OfflineCache::indexOf(int trackId) const{
    for(size_t index=0;index<trackIds.size();index++){
        if(trackIds[index]==trackId){
            return static_cast<int>(index);
        }
    }
    return NOT_CACHED;
}

void OfflineCache::removeAt(int index){
    trackIds.erase(trackIds.begin()+index);
    sizes.erase(sizes.begin()+index);
    storedTimes.erase(storedTimes.begin()+index);
}

void OfflineCache::put(int trackId,long long sizeBytes,long long now){
    if(sizeBytes>maxSize){
        throw DownloadException("file is larger than the offline cache","track "+std::to_string(trackId));
    }
    int existing=indexOf(trackId);
    if(existing!=NOT_CACHED){
        removeAt(existing);
    }
    long long usedBytes=0;
    for(long long size:sizes){
        usedBytes+=size;
    }
    while(usedBytes+sizeBytes>maxSize){
        usedBytes-=sizes.front();
        removeAt(0);
    }
    trackIds.push_back(trackId);
    sizes.push_back(sizeBytes);
    storedTimes.push_back(now);
}

long long OfflineCache::get(int trackId,long long now){
    int index=indexOf(trackId);
    if(index==NOT_CACHED){
        throw TrackNotFoundException("track is not cached: "+std::to_string(trackId),trackId);
    }
    if(now-storedTimes[index]>ttl){
        removeAt(index);
        throw TrackNotFoundException("cached track expired: "+std::to_string(trackId),trackId);
    }
    return sizes[index];
}