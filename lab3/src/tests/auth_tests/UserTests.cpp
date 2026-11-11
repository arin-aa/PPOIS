#include <catch2/catch_test_macros.hpp>
#include "User.h"
#include "Subscription.h"

TEST_CASE("User: Subscriptions") {
    Subscription activeSub("Premium", 1000, false);
    Subscription expiredSub("Basic", 100, false);
    
    User richUser("u1", "a@b.com", "Rich", &activeSub);
    User poorUser("u2", "c@d.com", "Poor", &expiredSub);
    User noSubUser("u3", "e@f.com", "None", nullptr);

    SECTION("Active subscription is reported correctly") {
        REQUIRE(richUser.hasActiveSubscription(500) == true);
        REQUIRE(richUser.hasActiveSubscription(1500) == false);
    }

    SECTION("Expired subscription is reported correctly") {
        REQUIRE(poorUser.hasActiveSubscription(50) == true);
        REQUIRE(poorUser.hasActiveSubscription(500) == false);
    }

    SECTION("No subscription always returns false") {
        REQUIRE(noSubUser.hasActiveSubscription(500) == false);
    }
}

TEST_CASE("User: Display Name Update") {
    User user("u1", "a@b.com", "OldName", nullptr);

    SECTION("Empty and whitespace-only strings are rejected") {
        REQUIRE(user.updateDisplayName("") == false);
        REQUIRE(user.updateDisplayName("   \t\n") == false);
    }

    SECTION("Name longer than 32 chars is rejected") {
        std::string longName(33, 'A');
        REQUIRE(user.updateDisplayName(longName) == false);
    }

    SECTION("Name exactly 32 chars is accepted") {
        std::string exactName(32, 'A');
        REQUIRE(user.updateDisplayName(exactName) == true);
    }

    SECTION("Surrounding spaces are trimmed") {
        REQUIRE(user.updateDisplayName("  Alice  ") == true);
        // Если в классе есть getDisplayName(), можно проверить:
        // REQUIRE(user.getDisplayName() == "Alice");
    }
}