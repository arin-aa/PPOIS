#include "PlaybackHistory.h"

const size_t MAX_HISTORY_SIZE=500;

PlaybackHistory::PlaybackHistory(const std::string& userId):userId(userId){}

void PlaybackHistory::add(const PlaybackSession& session){
    if(sessions.size()>=MAX_HISTORY_SIZE){
        sessions.erase(sessions.begin());
    }
    sessions.push_back(session);
}

std::vector<PlaybackSession> PlaybackHistory::getRecent(int count) const{
    std::vector<PlaybackSession> recent;
    for(auto session=sessions.rbegin();session!=sessions.rend() && static_cast<int>(recent.size())<count;++session){
        recent.push_back(*session);
    }
    return recent;
}

const std::vector<PlaybackSession>& PlaybackHistory::getSessions() const{
    return sessions;
}

const std::string& PlaybackHistory::getUserId() const{
    return userId;
}