#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "Subscription.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("Subscription: Activity and Renewal") {
    SECTION("isActive checks correctly") {
        Subscription sub("Premium", 1000, false);
        REQUIRE(sub.isActive(999) == true);
        REQUIRE(sub.isActive(1000) == false); // граница: в момент истечения не активна
        REQUIRE(sub.isActive(1001) == false);
    }

    SECTION("Renew active plan adds time to expiresAt") {
        Subscription sub("Premium", 1000, false);
        // now = 500 (активна до 1000). Продлеваем на 1000.
        // max(500, 1000) + 1000 = 2000
        REQUIRE(sub.renew(500, 1000) == 2000);
    }

    SECTION("Renew expired plan with auto-renew adds time to now") {
        Subscription sub("Premium", 1000, true);
        // now = 2000 (истекла). Продлеваем на 1000.
        // max(2000, 1000) + 1000 = 3000
        REQUIRE(sub.renew(2000, 1000) == 3000);
    }

    SECTION("Renew expired plan without auto-renew throws") {
        Subscription sub("Premium", 1000, false);
        REQUIRE_THROWS_AS(sub.renew(2000, 1000), SubscriptionExpiredException);
    }

    SECTION("Zero or negative period does nothing") {
        Subscription sub("Premium", 1000, true);
        REQUIRE(sub.renew(2000, 0) == 1000);
        REQUIRE(sub.renew(2000, -500) == 1000);
    }
}