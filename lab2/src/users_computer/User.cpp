#include "User.h"
#include "ComputerExceptions.h"

const int MAX_FAILED_ATTEMPTS=5;

User::User():login(""),password(""),isBlocked(false),failedAttempts(0){}

User::User(const std::string& login,const std::string& password):login(login),password(password),isBlocked(false),failedAttempts(0){}

bool User::authenticate(const std::string& candidate){
    if(isBlocked){
        throw UnauthorizedAccessException("user is blocked");
    }
    if(candidate==password){
        failedAttempts=0;
        return true;
    }
    failedAttempts++;
    if(failedAttempts>=MAX_FAILED_ATTEMPTS){
        isBlocked=true;
    }
    return false;
}

bool User::changePassword(const std::string& oldPassword,const std::string& newPassword){
    if(oldPassword!=password || newPassword.empty()){
        return false;
    }
    password=newPassword;
    return true;
}

int User::getFailedAttempts(){
    return failedAttempts;
}

bool User::isLocked(){
    return isBlocked;
}
