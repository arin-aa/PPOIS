#include "TimedLyric.h"

TimedLyric::TimedLyric(int startMs,const std::string& text):startMs(startMs),text(text){}

bool TimedLyric::isActiveAt(int positionMs,int endMs) const{
    return positionMs>=startMs && positionMs<endMs;
}

int TimedLyric::getStartMs() const{
    return startMs;
}

const std::string& TimedLyric::getText() const{
    return text;
}