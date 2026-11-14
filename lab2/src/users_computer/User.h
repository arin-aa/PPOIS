/**
 * @file User.h
 * @brief Declaration of the base class User.
 */
#pragma once
#include <string>

/**
 * @class User
 * @brief Base class of the system user.
 * 
 * Contains login, password, and authentication logic with protection against password guessing.
 */
class User{
protected:
    std::string login;///<User login.
    std::string password;///<User password.
    bool isBlocked;///<Account blocking flag.
    int failedAttempts;///<Counter of failed login attempts.

public:
/**
 * @brief Default constructor.
 */
    User();

/**
 * @brief Constructor with parameters.
 * @param login Login.
 * @param password Password.
 */
    User(const std::string& login,const std::string& password);

/**
 * @brief Virtual default destructor.
 */
    virtual ~User()=default;

/**
 * @brief Authenticates the user.
 * 
 * After 3 consecutive failed attempts, the account is blocked.
 * @param candidate Entered password.
 * @return true if the password is correct.
 * @exception UnauthorizedAccessException if the account is blocked.
 */
    bool authenticate(const std::string& candidate);

/**
 * @brief Changes the user password.
 * @param oldPassword Old password.
 * @param newPassword New password.
 * @exception UnauthorizedAccessException if the old password is incorrect or the account is blocked.
 * @exception InvalidConfigurationException if the new password is too short.
 */
    void changePassword(const std::string& oldPassword,const std::string& newPassword);
};