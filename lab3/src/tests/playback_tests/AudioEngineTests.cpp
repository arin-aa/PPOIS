#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "AudioEngine.h"
#include "AudioFile.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("AudioEngine: Load, Play and Position") {
    AudioEngine engine;
    AudioFile goodFile("a.mp3", "mp3", 320, 100);
    AudioFile badFile("b.mp3", "mp3", 0, 100);

    SECTION("Load null or corrupted file throws") {
        REQUIRE_THROWS_AS(engine.load(nullptr), AudioEngineException);
        REQUIRE_THROWS_AS(engine.load(&badFile), AudioEngineException);
    }

    SECTION("Play without file throws") {
        REQUIRE_THROWS_AS(engine.play(), AudioEngineException);
    }

    SECTION("Successful load and play") {
        REQUIRE_NOTHROW(engine.load(&goodFile));
        REQUIRE_NOTHROW(engine.play());
        REQUIRE_NOTHROW(engine.pause());
    }

    SECTION("setPosition clamps negative values to 0") {
        REQUIRE_NOTHROW(engine.setPosition(-100));
        REQUIRE_NOTHROW(engine.setPosition(100));
    }
}