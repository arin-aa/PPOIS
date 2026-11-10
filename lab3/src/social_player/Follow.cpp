#include "Follow.h"

Follow::Follow(const std::string& followerId,const std::string& followedUserId,long long createdAt):
    followerId(followerId),followedUserId(followedUserId),createdAt(createdAt){}

bool Follow::isMutual(const Follow& other) const{
    return other.followerId==followedUserId && other.followedUserId==followerId;
}

const std::string& Follow::getFollowedUserId() const{
    return followedUserId;
}