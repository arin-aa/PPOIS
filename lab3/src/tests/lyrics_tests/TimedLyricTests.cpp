#include <catch2/catch_test_macros.hpp>
#include "TimedLyric.h"

TEST_CASE("TimedLyric: Active state and Getters") {
    TimedLyric lyric(1000, "Hello");

    SECTION("Getters return correct values") {
        REQUIRE(lyric.getStartMs() == 1000);
        REQUIRE(lyric.getText() == "Hello");
    }

    SECTION("isActiveAt checks boundaries correctly") {
        // Интервал: [1000, 2000)
        REQUIRE(lyric.isActiveAt(999, 2000) == false);  // до начала
        REQUIRE(lyric.isActiveAt(1000, 2000) == true);  // ровно в начале (включительно)
        REQUIRE(lyric.isActiveAt(1500, 2000) == true);  // в середине
        REQUIRE(lyric.isActiveAt(1999, 2000) == true);  // за миг до конца
        REQUIRE(lyric.isActiveAt(2000, 2000) == false); // ровно в конце (не включительно)
        REQUIRE(lyric.isActiveAt(2001, 2000) == false); // после конца
    }
}