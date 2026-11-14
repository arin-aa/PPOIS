#include <catch2/catch_test_macros.hpp>
#include "SearchQuery.h"

TEST_CASE("SearchQuery: Normalization") {
    SECTION("Empty and whitespace-only strings normalize to empty") {
        REQUIRE(SearchQuery("").normalize() == "");
        REQUIRE(SearchQuery("   \t\n").normalize() == "");
        REQUIRE(SearchQuery("!@#$%^&*()").normalize() == "");
    }

    SECTION("Converts to lowercase and removes punctuation") {
        REQUIRE(SearchQuery("Hello, World!").normalize() == "hello world");
        REQUIRE(SearchQuery("RADIO!!").normalize() == "radio");
    }

    SECTION("Multiple spaces and punctuation collapse to a single space") {
        REQUIRE(SearchQuery("  a...b  , c  ").normalize() == "a b c");
    }
}

TEST_CASE("SearchQuery: IsEmpty and WantsType") {
    SECTION("isEmpty checks normalized text") {
        REQUIRE(SearchQuery("   ").isEmpty() == true);
        REQUIRE(SearchQuery("a").isEmpty() == false);
    }

    SECTION("wantsType acts as a filter") {
        SearchQuery any("text", "");
        SearchQuery onlyTracks("text", "track");
        
        REQUIRE(any.wantsType("album") == true);
        REQUIRE(any.wantsType("track") == true);
        
        REQUIRE(onlyTracks.wantsType("track") == true);
        REQUIRE(onlyTracks.wantsType("album") == false);
    }
}