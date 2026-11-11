#include <catch2/catch_test_macros.hpp>
#include "Follow.h"

TEST_CASE("Follow: Mutual check and Getters") {
    // userA подписан на userB
    Follow followAtoB("userA", "userB", 1000);
    // userB подписан на userA
    Follow followBtoA("userB", "userA", 2000);
    // userC подписан на userA
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