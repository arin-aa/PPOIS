#include <catch2/catch_test_macros.hpp>
#include "Genre.h"

TEST_CASE("Genre: Subgenre check") {
    Genre rock(1, "rock");
    Genre punk(2, "rock/punk");
    Genre rockstar(3, "rockstar");

    SECTION("Direct subgenre returns true") {
        REQUIRE(punk.isSubgenreOf(rock) == true);
    }

    SECTION("Similar name without separator returns false") {
        REQUIRE(rockstar.isSubgenreOf(rock) == false);
    }

    SECTION("Genre is not a subgenre of itself") {
        REQUIRE(rock.isSubgenreOf(rock) == false);
    }
}