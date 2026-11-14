/**
 * @file Subscription.h
 * @brief Declaration of the Subscription class.
 */
#pragma once
#include <string>

/**
 * @class Subscription
 * @brief Plan of a user with an expiration time.
 */
class Subscription{
private:
    std::string plan;///<Name of the plan.
    long long expiresAt;///<Moment when the plan expires (ms).
    bool autoRenew;///<Whether the plan is renewed automatically.

public:
/**
 * @brief Constructor with parameters.
 * @param plan Name of the plan.
 * @param expiresAt Moment when the plan expires (ms).
 * @param autoRenew Whether the plan is renewed automatically.
 */
    Subscription(const std::string& plan,long long expiresAt,bool autoRenew);

/**
 * @brief Checks whether the plan is still valid.
 * @param now Current time (ms).
 * @return true if the plan has not expired yet.
 */
    bool isActive(long long now) const;

/**
 * @brief Extends the plan by a period.
 *
 * The period is added to the expiration time, or to the current time if the plan already expired.
 * @param now Current time (ms).
 * @param periodMs Length of the extension (ms), a period that is not positive changes nothing.
 * @return Expiration time after the extension (ms).
 * @exception SubscriptionExpiredException if the plan has expired and auto renewal is off.
 */
    long long renew(long long now,long long periodMs);
};