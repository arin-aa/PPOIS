#pragma once
#include <string>

class User{
protected:
    std::string login;
    std::string password;
    bool isBlocked;
    int failedAttempts;

public:
    User();
    User(const std::string& login,const std::string& password);
    virtual ~User()=default;

    bool authenticate(const std::string& pass);
    bool changePassword(const std::string& oldPass,const std::string& newPass);
};