#include "OfflineCache.h"
#include "MusicPlayerExceptions.h"

static long long usedSize(const std::map<int,std::pair<long long,long long>>& entries){
    long long usedBytes=0;
    for(const auto& entry:entries){
        usedBytes+=entry.second.first;
    }
    return usedBytes;
}

static void evictOldest(std::map<int,std::pair<long long,long long>>& entries){
    auto oldest=entries.begin();
    for(auto entry=entries.begin();entry!=entries.end();++entry){
        long long entryTime=entry->second.second;
        long long oldestTime=oldest->second.second;
        if(entryTime<oldestTime){
            oldest=entry;
        }
    }
    entries.erase(oldest);
}

OfflineCache::OfflineCache(long long maxSize,long long ttl):maxSize(maxSize),ttl(ttl){}

void OfflineCache::put(int trackId,long long sizeBytes,long long now){
    if(sizeBytes>maxSize){
        throw DownloadException("file is larger than the offline cache","track "+std::to_string(trackId));
    }
    entries.erase(trackId);
    while(usedSize(entries)+sizeBytes>maxSize){
        evictOldest(entries);
    }
    entries[trackId]=std::make_pair(sizeBytes,now);
}

long long OfflineCache::get(int trackId,long long now){
    auto found=entries.find(trackId);
    if(found==entries.end()){
        throw TrackNotFoundException("track is not cached: "+std::to_string(trackId),trackId);
    }
    long long timestamp=found->second.second;
    long long age=now-timestamp;
    if(age>ttl){
        entries.erase(found);
        throw TrackNotFoundException("cached track expired: "+std::to_string(trackId),trackId);
    }
    return found->second.first;
}