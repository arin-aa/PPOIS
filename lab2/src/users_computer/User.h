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

    bool authenticate(const std::string& candidate);
    bool changePassword(const std::string& oldPassword,const std::string& newPassword);
    int getFailedAttempts();
    bool isLocked();
};
