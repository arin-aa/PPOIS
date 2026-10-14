#include "User.h"
#include "ComputerExceptions.h"

User::User():login(""),password(""),isBlocked(false),failedAttempts(0){}

User::User(const std::string& login,const std::string& password):login(login),password(password),isBlocked(false),failedAttempts(0){}

bool User::authenticate(const std::string& pass){
    if(isBlocked){
        throw UnauthorizedAccessException("user is blocked");
    }
    if(pass==password){
        failedAttempts=0;
        return true;
    }
    failedAttempts++;
    if(failedAttempts>=5){
        isBlocked=true;
    }
    return false;
}

bool User::changePassword(const std::string& oldPass,const std::string& newPass){
    if(oldPass!=password){
        return false;
    }
    if(newPass.empty()){
        return false;
    }
    password=newPass;
    return true;
}