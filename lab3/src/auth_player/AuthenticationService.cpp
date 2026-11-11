#include "AuthenticationService.h"
#include "MusicPlayerExceptions.h"
#include "User.h"

const int MAX_ATTEMPTS=5;
const size_t MIN_PASSWORD_LENGTH=8;
const std::string DIGITS="0123456789";

AuthenticationService::AuthenticationService():currentUser(nullptr),attempts(0){}

User* AuthenticationService::signIn(User* user,const std::string& password){
    if(!user){
        throw UserNotFoundException("user is not specified","");
    }
    if(attempts>=MAX_ATTEMPTS){
        throw InvalidPasswordException("too many failed attempts for "+user->getEmail(),LOCKOUT_REASON);
    }
    bool isLongEnough=password.size()>=MIN_PASSWORD_LENGTH;
    bool hasDigit=password.find_first_of(DIGITS)!=std::string::npos;
    if(!isLongEnough || !hasDigit){
        attempts++;
        throw AuthenticationException("wrong password for "+user->getEmail(),attempts);
    }
    attempts=0;
    currentUser=user;
    return user;
}

void AuthenticationService::signOut(){
    currentUser=nullptr;
}