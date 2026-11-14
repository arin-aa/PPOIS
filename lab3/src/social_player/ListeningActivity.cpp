#include "ListeningActivity.h"

ListeningActivity::ListeningActivity(const std::string& userId,Track* track,long long listenedAt):
    userId(userId),track(track),listenedAt(listenedAt){}

bool ListeningActivity::isRecent(long long now,long long windowMs) const{
    return now-listenedAt<=windowMs;
}

const std::string& ListeningActivity::getUserId() const{
    return userId;
}

long long ListeningActivity::getListenedAt() const{
    return listenedAt;
}