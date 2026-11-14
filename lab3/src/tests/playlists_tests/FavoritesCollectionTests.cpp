#include <catch2/catch_test_macros.hpp>
#include "FavoritesCollection.h"

TEST_CASE("FavoritesCollection: Toggle and Contains") {
    FavoritesCollection favorites("user1");

    SECTION("Initially empty") {
        REQUIRE(favorites.contains(1) == false);
    }

    SECTION("Toggle adds a track and returns true") {
        REQUIRE(favorites.toggle(1, 1000) == true);
        REQUIRE(favorites.contains(1) == true);
    }

    SECTION("Toggle removes an existing track and returns false") {
        favorites.toggle(1, 1000);
        REQUIRE(favorites.toggle(1, 2000) == false);
        REQUIRE(favorites.contains(1) == false);
    }

    SECTION("Multiple tracks can be added independently") {
        favorites.toggle(1, 1000);
        favorites.toggle(2, 2000);
        REQUIRE(favorites.contains(1) == true);
        REQUIRE(favorites.contains(2) == true);
        
        favorites.toggle(1, 3000);
        REQUIRE(favorites.contains(1) == false);
        REQUIRE(favorites.contains(2) == true);
    }
}