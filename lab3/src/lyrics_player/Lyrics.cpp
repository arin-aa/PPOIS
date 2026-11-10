#include "Lyrics.h"
#include <limits>
#include "MusicPlayerExceptions.h"

const int LAST_LINE_END=std::numeric_limits<int>::max();

Lyrics::Lyrics(int trackId,const std::vector<TimedLyric>& lines,const std::string& source):
    trackId(trackId),lines(lines),source(source){
    for(size_t index=1;index<lines.size();index++){
        if(lines[index].getStartMs()<=lines[index-1].getStartMs()){
            throw MetadataException("lyrics lines are not in time order",source);
        }
    }
}

std::string Lyrics::getLineAt(int positionMs) const{
    for(size_t index=0;index<lines.size();index++){
        size_t nextIndex=index+1;
        bool isLast=(nextIndex==lines.size());
        int endMs=isLast?LAST_LINE_END:lines[nextIndex].getStartMs();
        if(lines[index].isActiveAt(positionMs,endMs)){
            return lines[index].getText();
        }
    }
    return "";
}