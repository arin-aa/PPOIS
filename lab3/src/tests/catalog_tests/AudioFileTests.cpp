#include <catch2/catch_test_macros.hpp>
#include "AudioFile.h"

TEST_CASE("AudioFile: Properties and Lossless check") {
    SECTION("Lossless formats return true") {
        AudioFile f1("a.flac", "flac", 1000, 100);
        AudioFile f2("a.wav", "wav", 1000, 100);
        AudioFile f3("a.alac", "alac", 1000, 100);
        REQUIRE(f1.isLossless() == true);
        REQUIRE(f2.isLossless() == true);
        REQUIRE(f3.isLossless() == true);
    }

    SECTION("Lossy formats return false") {
        AudioFile f1("a.mp3", "mp3", 320, 100);
        REQUIRE(f1.isLossless() == false);
    }

    SECTION("Getters and Extension format") {
        AudioFile f("a.mp3", "mp3", 320, 100);
        REQUIRE(f.getExtension() == ".mp3");
        REQUIRE(f.getUri() == "a.mp3");
        REQUIRE(f.getBitrate() == 320);
    }
}