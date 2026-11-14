#include "UserProfile.h"

UserProfile::UserProfile(const std::string& userId,const std::string& bio,const std::string& country):
    userId(userId),bio(bio),country(country){}

bool UserProfile::isComplete() const{
    return !bio.empty() && !country.empty();
}