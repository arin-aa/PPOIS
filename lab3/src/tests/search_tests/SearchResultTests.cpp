#include <catch2/catch_test_macros.hpp>
#include "SearchResult.h"
#include "Track.h"
#include "Album.h"
#include "Artist.h"

TEST_CASE("SearchResult: Top Result and Count") {
    Track t1(1, "Track Title", 1, 1, 1000, nullptr);
    Album a1(1, "Album Title", 1, {});
    Artist ar1(1, "Artist Name", {}, "");

    SECTION("Empty result returns empty string and 0 count") {
        SearchResult res({}, {}, {});
        REQUIRE(res.getTopResult() == "");
        REQUIRE(res.getTotalCount() == 0);
    }

    SECTION("Top result prioritizes tracks, then albums, then artists") {
        SearchResult trackRes({&t1}, {&a1}, {&ar1});
        REQUIRE(trackRes.getTopResult() == "Track Title");

        SearchResult albumRes({}, {&a1}, {&ar1});
        REQUIRE(albumRes.getTopResult() == "Album Title");

        SearchResult artistRes({}, {}, {&ar1});
        REQUIRE(artistRes.getTopResult() == "Artist Name");
    }

    SECTION("Total count sums all entities") {
        SearchResult res({&t1}, {&a1}, {&ar1});
        REQUIRE(res.getTotalCount() == 3);
    }
}