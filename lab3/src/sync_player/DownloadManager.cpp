#include "DownloadManager.h"
#include <algorithm>
#include "MusicPlayerExceptions.h"

DownloadManager::DownloadManager(int maxConcurrent):activeCount(0),maxConcurrent(maxConcurrent){}

bool DownloadManager::start(int trackId,const std::string& url){
    if(url.empty()){
        throw DownloadException("track has no address: "+std::to_string(trackId),url);
    }
    if(activeCount>=maxConcurrent){
        queue.push_back(trackId);
        return false;
    }
    activeCount++;
    return true;
}

void DownloadManager::cancel(int trackId){
    auto waiting=std::find(queue.begin(),queue.end(),trackId);
    if(waiting!=queue.end()){
        queue.erase(waiting);
        return;
    }
    if(activeCount==0){
        throw TrackNotFoundException("nothing to cancel for track "+std::to_string(trackId),trackId);
    }
    activeCount--;
    if(!queue.empty()){
        queue.erase(queue.begin());
        activeCount++;
    }
}

int DownloadManager::getQueueSize() const{
    return static_cast<int>(queue.size());
}

int DownloadManager::getActiveCount() const{
    return activeCount;
}