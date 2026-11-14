/**
 * @file Follow.h
 * @brief Declaration of the Follow class.
 */
#pragma once
#include <string>

/**
 * @class Follow
 * @brief Subscription of one user to the activity of another user.
 */
class Follow{
private:
    std::string followerId;///<Identifier of the user who follows.
    std::string followedUserId;///<Identifier of the user who is followed.
    long long createdAt;///<Moment when the subscription was created (ms).

public:
/**
 * @brief Constructor with parameters.
 * @param followerId Identifier of the user who follows.
 * @param followedUserId Identifier of the user who is followed.
 * @param createdAt Moment of creation (ms).
 */
    Follow(const std::string& followerId,const std::string& followedUserId,long long createdAt);

/**
 * @brief Checks whether two users follow each other.
 * @param other Subscription to compare with.
 * @return true if the other subscription goes in the opposite direction.
 */
    bool isMutual(const Follow& other) const;

/**
 * @brief Returns the user who is followed.
 * @return Identifier of the followed user.
 */
    const std::string& getFollowedUserId() const;
};