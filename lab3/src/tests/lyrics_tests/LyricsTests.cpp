#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "Lyrics.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("Lyrics: Constructor validation") {
    SECTION("Empty and single line lists are valid") {
        REQUIRE_NOTHROW(Lyrics(1, {}, "src"));
        REQUIRE_NOTHROW(Lyrics(1, {TimedLyric(100, "A")}, "src"));
    }

    SECTION("Strictly increasing times are valid") {
        REQUIRE_NOTHROW(Lyrics(1, {
            TimedLyric(100, "A"), 
            TimedLyric(200, "B"), 
            TimedLyric(300, "C")
        }, "src"));
    }

    SECTION("Equal times throw MetadataException") {
        REQUIRE_THROWS_AS(Lyrics(1, {
            TimedLyric(100, "A"), 
            TimedLyric(100, "B")
        }, "src"), MetadataException);
    }

    SECTION("Decreasing times throw MetadataException") {
        REQUIRE_THROWS_AS(Lyrics(1, {
            TimedLyric(200, "A"), 
            TimedLyric(100, "B")
        }, "src"), MetadataException);
    }
}

TEST_CASE("Lyrics: getLineAt logic") {
    // Интервалы: [1000, 3000) -> "A", [3000, LAST_LINE_END) -> "B"
    std::vector<TimedLyric> lines = {
        TimedLyric(1000, "A"),
        TimedLyric(3000, "B")
    };
    Lyrics lyrics(1, lines, "src");

    SECTION("Empty lyrics returns empty string") {
        Lyrics empty(1, {}, "src");
        REQUIRE(empty.getLineAt(1000) == "");
    }

    SECTION("Before the first line returns empty") {
        REQUIRE(lyrics.getLineAt(999) == "");
        REQUIRE(lyrics.getLineAt(-1) == "");
    }

    SECTION("Exactly at start of line returns it") {
        REQUIRE(lyrics.getLineAt(1000) == "A");
    }

    SECTION("Between lines returns the first one") {
        REQUIRE(lyrics.getLineAt(2000) == "A");
    }

    SECTION("Exactly at start of next line returns the next one") {
        // Граница 3000: endMs первой строки равен 3000, поэтому она уже неактивна
        REQUIRE(lyrics.getLineAt(3000) == "B");
    }

    SECTION("After the last line starts returns the last one") {
        // Для последней строки endMs = LAST_LINE_END (INT_MAX)
        REQUIRE(lyrics.getLineAt(999999) == "B");
    }
}