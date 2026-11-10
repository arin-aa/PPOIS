#include "AuthenticationService.h"
#include <algorithm>
#include <cctype>
#include "MusicPlayerExceptions.h"
#include "User.h"

const int MAX_ATTEMPTS=5;
const size_t MIN_PASSWORD_LENGTH=8;

static bool isAcceptable(const std::string& password){
    return password.size() >= MIN_PASSWORD_LENGTH
        && password.find_first_of("0123456789") != std::string::npos;
}

AuthenticationService::AuthenticationService():currentUser(nullptr),attempts(0){}

User* AuthenticationService::signIn(User* user,const std::string& password){
    if(!user){
        throw UserNotFoundException("user is not specified","");
    }
    if(attempts>=MAX_ATTEMPTS){
        throw InvalidPasswordException("too many failed attempts for "+user->getEmail(),LOCKOUT_REASON);
    }
    if(!isAcceptable(password)){
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

User* AuthenticationService::getCurrentUser() const{
    return currentUser;
}