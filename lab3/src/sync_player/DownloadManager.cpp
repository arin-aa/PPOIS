#include "DownloadManager.h"
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
    for(size_t index=0;index<queue.size();index++){
        if(queue[index]==trackId){
            queue.erase(queue.begin()+index);
            return;
        }
    }
    if(activeCount==0){
        throw TrackNotFoundException("nothing to cancel for track "+std::to_string(trackId),trackId);
    }
    if(queue.empty()){
        activeCount--;
    }else{
        queue.erase(queue.begin());
    }
}