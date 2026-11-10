#include "UserFeed.h"
#include <algorithm>
#include "Follow.h"
#include "ListeningActivity.h"

UserFeed::UserFeed(const std::string& userId,const std::vector<Follow*>& follows):userId(userId),follows(follows){}

std::vector<ListeningActivity*> UserFeed::build(const std::vector<ListeningActivity*>& activities,long long now,
                                                long long windowMs) const{
    std::vector<ListeningActivity*> feed;
    for(ListeningActivity* activity:activities){
        bool isFollowed=std::any_of(follows.begin(),follows.end(),[&](const Follow* follow){
            return follow->getFollowedUserId()==activity->getUserId();
        });
        if(isFollowed && activity->isRecent(now,windowMs)){
            feed.push_back(activity);
        }
    }
    std::sort(feed.begin(),feed.end(),[](const ListeningActivity* left,const ListeningActivity* right){
        return left->getListenedAt()>right->getListenedAt();
    });
    return feed;
}