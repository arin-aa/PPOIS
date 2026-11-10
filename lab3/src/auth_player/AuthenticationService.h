/**
 * @file AuthenticationService.h
 * @brief Declaration of the AuthenticationService class.
 */
#pragma once
#include <string>

class User;

/**
 * @class AuthenticationService
 * @brief Signs users in and out.
 *
 * A password is accepted if it has at least 8 symbols and contains a digit.
 */
class AuthenticationService{
private:
    User* currentUser;///<User who is signed in now, null if nobody.
    int attempts;///<Number of failed sign-in attempts in a row.

public:
/**
 * @brief Default constructor. Nobody is signed in.
 */
    AuthenticationService();

/**
 * @brief Signs a user in.
 * @param user User who signs in.
 * @param password Password entered by the user.
 * @return Pointer to the signed-in user.
 * @exception UserNotFoundException if the user is null.
 * @exception InvalidPasswordException if the account is locked after too many failed attempts.
 * @exception AuthenticationException if the password is not accepted.
 */
    User* signIn(User* user,const std::string& password);

/**
 * @brief Signs the current user out.
 */
    void signOut();

/**
 * @brief Returns the signed-in user.
 * @return Pointer to the current user, null if nobody is signed in.
 */
    User* getCurrentUser() const;
};