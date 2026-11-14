#include <catch2/catch_test_macros.hpp>
#include "Follow.h"

TEST_CASE("Follow: Mutual check and Getters") {
    Follow followAtoB("userA", "userB", 1000);
    Follow followBtoA("userB", "userA", 2000);
    Follow followCtoA("userC", "userA", 3000);

    SECTION("Mutual follow returns true") {
        REQUIRE(followAtoB.isMutual(followBtoA) == true);
        REQUIRE(followBtoA.isMutual(followAtoB) == true);
    }

    SECTION("One-way follow returns false") {
        REQUIRE(followAtoB.isMutual(followCtoA) == false);
    }

    SECTION("Self-follow or unrelated follow returns false") {
        REQUIRE(followAtoB.isMutual(followAtoB) == false);
    }

    SECTION("Getter returns correct followed user") {
        REQUIRE(followAtoB.getFollowedUserId() == "userB");
    }
}