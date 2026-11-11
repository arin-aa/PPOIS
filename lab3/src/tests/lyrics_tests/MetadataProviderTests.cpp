#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "MetadataProvider.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("MetadataProvider: Fetch and Errors") {
    SECTION("Empty URL throws MetadataException") {
        MetadataProvider provider("");
        REQUIRE_THROWS_AS(provider.fetchMetadata("song.mp3"), MetadataException);
    }

    SECTION("File without extension throws MetadataException") {
        MetadataProvider provider("http://api");
        REQUIRE_THROWS_AS(provider.fetchMetadata("path/to/song"), MetadataException);
    }

    SECTION("Valid file with path, extension and underscores") {
        MetadataProvider provider("http://api");
        auto meta = provider.fetchMetadata("music/queen_radio_ga_ga.mp3");
        
        REQUIRE(meta.size() == 3);
        REQUIRE(meta["title"] == "queen radio ga ga"); // подчеркивания заменены на пробелы
        REQUIRE(meta["format"] == "mp3");
        REQUIRE(meta["source"] == "http://api");
    }

    SECTION("File without path but with extension") {
        MetadataProvider provider("http://api");
        auto meta = provider.fetchMetadata("song.flac");
        
        REQUIRE(meta["title"] == "song");
        REQUIRE(meta["format"] == "flac");
    }
}