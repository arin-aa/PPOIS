/**
 * @file UserProfile.h
 * @brief Declaration of the UserProfile class.
 */
#pragma once
#include <string>

/**
 * @class UserProfile
 * @brief Public information a user tells about themselves.
 */
class UserProfile{
private:
    std::string userId;///<Identifier of the owner.
    std::string bio;///<Short biography.
    std::string country;///<Country of residence.

public:
/**
 * @brief Constructor with parameters.
 * @param userId Identifier of the owner.
 * @param bio Short biography.
 * @param country Country of residence.
 */
    UserProfile(const std::string& userId,const std::string& bio,const std::string& country);

/**
 * @brief Checks whether all information is filled in.
 * @return true if both the biography and the country are not empty.
 */
    bool isComplete() const;
};