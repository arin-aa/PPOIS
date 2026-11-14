#include <catch2/catch_test_macros.hpp>
#include "AppSettings.h"
#include <map>

TEST_CASE("AppSettings: Loading") {
    AppSettings settings;

    SECTION("Load with empty map does not crash") {
        std::map<std::string,std::string> emptyMap;
        REQUIRE_NOTHROW(settings.load(emptyMap));
    }

    SECTION("Load updates fields without crashing") {
        std::map<std::string,std::string> values = {
            {"volume", "80"},
            {"language", "ru"},
            {"repeatMode", "all"},
            {"theme", "dark"},
            {"crossfadeMs", "1500"}
        };
        REQUIRE_NOTHROW(settings.load(values));
    }

    SECTION("Unknown keys in map are ignored safely") {
        std::map<std::string,std::string> values = {
            {"volume", "30"},
            {"unknownKey", "someValue"}
        };
        REQUIRE_NOTHROW(settings.load(values));
    }
}