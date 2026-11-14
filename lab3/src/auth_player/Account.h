/**
 * @file Account.h
 * @brief Declaration of the Account class.
 */
#pragma once
#include <string>

/**
 * @class Account
 * @brief Account of a user with its status.
 */
class Account{
private:
    std::string id;///<Identifier of the account.
    std::string status;///<Status of the account: "active", "blocked" or "deleted".

public:
/**
 * @brief Constructor with parameters.
 * @param id Identifier of the account.
 * @param status Status of the account.
 */
    Account(const std::string& id,const std::string& status);

/**
 * @brief Checks whether the account is blocked.
 * @return true if the status is "blocked".
 */
    bool isBlocked() const;
};