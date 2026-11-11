#include "User.h"
#include "Subscription.h"

const size_t MAX_NAME_LENGTH=32;
const std::string WHITESPACE=" \t\r\n";

User::User(const std::string& id,const std::string& email,const std::string& displayName,Subscription* subscription):
    id(id),email(email),displayName(displayName),subscription(subscription){}

bool User::hasActiveSubscription(long long now) const{
    return subscription!=nullptr && subscription->isActive(now);
}

bool User::updateDisplayName(const std::string& newName){
    size_t first=newName.find_first_not_of(WHITESPACE);
    if(first==std::string::npos){
        return false;
    }
    size_t last=newName.find_last_not_of(WHITESPACE);
    std::string cleanName=newName.substr(first,last-first+1);
    if(cleanName.size()>MAX_NAME_LENGTH){
        return false;
    }
    displayName=cleanName;
    return true;
}

const std::string& User::getEmail() const{
    return email;
}