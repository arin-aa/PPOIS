#include <catch2/catch_test_macros.hpp>
#include "Account.h"

TEST_CASE("Account: Status checks") {
    SECTION("Blocked account is blocked") {
        Account acc("user1", "blocked");
        REQUIRE(acc.isBlocked() == true);
    }

    SECTION("Active account is not blocked") {
        Account acc("user1", "active");
        REQUIRE(acc.isBlocked() == false);
    }

    SECTION("Deleted account is not blocked") {
        Account acc("user1", "deleted");
        REQUIRE(acc.isBlocked() == false);
    }
}