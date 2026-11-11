/**
 * @file User.h
 * @brief Declaration of the User class.
 */
#pragma once
#include <string>

class Subscription;

/**
 * @class User
 * @brief Registered user of the music player.
 */
class User{
private:
    std::string id;///<Unique identifier of the user.
    std::string email;///<Email address of the user.
    std::string displayName;///<Name shown to other users.
    Subscription* subscription;///<Pointer to the subscription, may be null.

public:
/**
 * @brief Constructor with parameters.
 * @param id Unique identifier.
 * @param email Email address.
 * @param displayName Name shown to other users.
 * @param subscription Pointer to the subscription, may be null.
 */
    User(const std::string& id,const std::string& email,const std::string& displayName,Subscription* subscription);

/**
 * @brief Checks whether the user has a valid subscription.
 * @param now Current time (ms).
 * @return true if the subscription exists and has not expired.
 */
    bool hasActiveSubscription(long long now) const;

/**
 * @brief Changes the display name.
 * @param newName New name, surrounding spaces are removed.
 * @return true if the name was changed, false if it is empty or too long.
 */
    bool updateDisplayName(const std::string& newName);

/**
 * @brief Returns the email address.
 * @return Email address.
 */
    const std::string& getEmail() const;
};