#include <catch2/catch_test_macros.hpp>
#include "Artwork.h"

TEST_CASE("Artwork: Thumbnail URI generation") {
    SECTION("Path with extension") {
        Artwork art("cover.jpg");
        REQUIRE(art.getThumbnailUri() == "cover_thumb.jpg");
    }

    SECTION("Path without extension") {
        Artwork art("cover");
        REQUIRE(art.getThumbnailUri() == "cover_thumb");
    }

    SECTION("Path with multiple dots") {
        Artwork art("my.cover.v1.jpg");
        REQUIRE(art.getThumbnailUri() == "my.cover.v1_thumb.jpg");
    }
}