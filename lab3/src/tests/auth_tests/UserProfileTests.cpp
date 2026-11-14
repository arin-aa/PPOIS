#include <catch2/catch_test_macros.hpp>
#include "UserProfile.h"

TEST_CASE("UserProfile: IsComplete") {
    SECTION("Both fields filled is complete") {
        UserProfile prof("u1", "Hello", "Russia");
        REQUIRE(prof.isComplete() == true);
    }

    SECTION("Empty bio is incomplete") {
        UserProfile prof("u1", "", "Russia");
        REQUIRE(prof.isComplete() == false);
    }

    SECTION("Empty country is incomplete") {
        UserProfile prof("u1", "Hello", "");
        REQUIRE(prof.isComplete() == false);
    }

    SECTION("Both empty is incomplete") {
        UserProfile prof("u1", "", "");
        REQUIRE(prof.isComplete() == false);
    }
}