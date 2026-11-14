#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "RadioStation.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("RadioStation: TuneIn validation") {
    SECTION("Valid HTTP and HTTPS URLs") {
        RadioStation httpStation("Radio 1", "http://stream.radio.com");
        RadioStation httpsStation("Radio 2", "https://secure.radio.com");
        
        REQUIRE(httpStation.tuneIn() == "http://stream.radio.com");
        REQUIRE(httpsStation.tuneIn() == "https://secure.radio.com");
    }

    SECTION("Invalid URL protocols throw PlaybackException") {
        RadioStation ftpStation("Radio 3", "ftp://stream.radio.com");
        RadioStation noProtocol("Radio 4", "stream.radio.com");
        
        REQUIRE_THROWS_AS(ftpStation.tuneIn(), PlaybackException);
        REQUIRE_THROWS_AS(noProtocol.tuneIn(), PlaybackException);
    }
}

TEST_CASE("RadioStation: Classify Genre") {
    RadioStation station("Classic Rock & Roll FM", "http://r.fm");
    
    SECTION("Finds genre inside station name") {
        std::vector<std::string> genres = {"jazz", "rock", "pop"};
        REQUIRE(station.classifyGenre(genres) == "rock");
    }

    SECTION("Ignores case and punctuation") {
        RadioStation lofi("LOFI beats", "http://r.fm");
        REQUIRE(lofi.classifyGenre({"lofi"}) == "lofi");
        REQUIRE(lofi.classifyGenre({"lofi beats"}) == "lofi beats");
    }

    SECTION("Returns empty string if no genre matches") {
        REQUIRE(station.classifyGenre({"metal", "jazz"}).empty());
    }

    SECTION("Returns empty string if genre list is empty") {
        REQUIRE(station.classifyGenre({}).empty());
    }
}