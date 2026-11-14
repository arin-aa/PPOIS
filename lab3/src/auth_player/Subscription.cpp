#include "Subscription.h"
#include "MusicPlayerExceptions.h"

Subscription::Subscription(const std::string& plan,long long expiresAt,bool autoRenew):plan(plan),expiresAt(expiresAt),autoRenew(autoRenew){}

bool Subscription::isActive(long long now) const{
    return now<expiresAt;
}

long long Subscription::renew(long long now,long long periodMs){
    if(!isActive(now) && !autoRenew){
        throw SubscriptionExpiredException(plan+" has expired and is not renewed automatically",expiresAt);
    }
    if(periodMs>0){
        long long startMs=expiresAt>now?expiresAt:now;
        expiresAt=startMs+periodMs;
    }
    return expiresAt;
}