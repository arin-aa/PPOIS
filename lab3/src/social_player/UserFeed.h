/**
 * @file UserFeed.h
 * @brief Declaration of the UserFeed class.
 */
#pragma once
#include <string>
#include <vector>

class Follow;
class ListeningActivity;

/**
 * @class UserFeed
 * @brief Recent activity of the users that somebody follows.
 */
class UserFeed{
private:
    std::string userId;///<Identifier of the owner of the feed.
    std::vector<Follow*> follows;///<Subscriptions of the owner.

public:
/**
 * @brief Constructor with parameters.
 * @param userId Identifier of the owner.
 * @param follows Subscriptions of the owner.
 */
    UserFeed(const std::string& userId,const std::vector<Follow*>& follows);

/**
 * @brief Builds the feed from all known activities.
 * @param activities Activities of all users.
 * @param now Current time (ms).
 * @param windowMs Length of the period that counts as recent (ms).
 * @return Recent activities of followed users, the newest first.
 */
    std::vector<ListeningActivity*> build(const std::vector<ListeningActivity*>& activities,long long now,
                                          long long windowMs) const;
};