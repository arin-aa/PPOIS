#include "UserFeed.h"
#include "Follow.h"
#include "ListeningActivity.h"

UserFeed::UserFeed(const std::string& userId,const std::vector<Follow*>& follows):userId(userId),follows(follows){}

std::vector<ListeningActivity*> UserFeed::build(const std::vector<ListeningActivity*>& activities,long long now,
                                                long long windowMs) const{
    std::vector<ListeningActivity*> feed;
    for(ListeningActivity* activity:activities){
        bool isFollowed=false;
        for(const Follow* follow:follows){
            if(follow->getFollowedUserId()==activity->getUserId()){
                isFollowed=true;
            }
        }
        if(!isFollowed || !activity->isRecent(now,windowMs)){
            continue;
        }
        size_t position=0;
        while(position<feed.size() && feed[position]->getListenedAt()>activity->getListenedAt()){
            position++;
        }
        feed.insert(feed.begin()+position,activity);
    }
    return feed;
}