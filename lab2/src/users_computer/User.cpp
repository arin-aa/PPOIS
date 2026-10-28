#include "User.h"
#include "ComputerExceptions.h"

const int MAX_FAILS=3;
const int MIN_LENGTH=6;

User::User():login(""),password(""),isBlocked(false),failedAttempts(0){}

User::User(const std::string& login,const std::string& password):login(login),password(password),isBlocked(false),failedAttempts(0){}

bool User::authenticate(const std::string& candidate){
    if(isBlocked){
        throw UnauthorizedAccessException(login+" is blocked");
    }
    if(candidate==password){
        failedAttempts=0;
        return true;
    }
    failedAttempts++;
    isBlocked=failedAttempts>=MAX_FAILS;
    return false;
}

void User::changePassword(const std::string& oldPassword,const std::string& newPassword){
    if(!authenticate(oldPassword)){
        throw UnauthorizedAccessException("wrong password for "+login);
    }
    if(static_cast<int>(newPassword.size())<MIN_LENGTH){
        throw InvalidConfigurationException("new password is too short");
    }
    password=newPassword;
}
