#include "Queue.h"
#include "MusicPlayerExceptions.h"

const std::string REPEAT_ONE="one";
const std::string REPEAT_ALL="all";

Queue::Queue(const std::string& repeatMode):currentIndex(0),repeatMode(repeatMode){}

Track* Queue::next(){
    Track* current=getCurrent();
    if(repeatMode==REPEAT_ONE){
        return current;
    }
    if(static_cast<size_t>(currentIndex)+1<items.size()){
        currentIndex++;
    }else if(repeatMode==REPEAT_ALL){
        currentIndex=0;
    }else{
        throw PlaybackException("the end of the queue is reached",0);
    }
    return getCurrent();
}

Track* Queue::previous(){
    Track* current=getCurrent();
    if(repeatMode==REPEAT_ONE){
        return current;
    }
    if(currentIndex>0){
        currentIndex--;
    }else if(repeatMode==REPEAT_ALL){
        currentIndex=static_cast<int>(items.size())-1;
    }
    return getCurrent();
}

void Queue::add(Track* track){
    items.push_back(track);
}

Track* Queue::getCurrent() const{
    if(items.empty()){
        throw PlaybackException("the queue is empty",0);
    }
    return items[static_cast<size_t>(currentIndex)];
}