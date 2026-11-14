#include <catch2/catch_test_macros.hpp>
#include "AppTheme.h"

TEST_CASE("AppTheme: Dark Mode Toggle") {
    SECTION("Toggle from light to dark and back") {
        AppTheme theme("Classic", false, "blue");
        
        REQUIRE(theme.toggleDarkMode() == true);
        REQUIRE(theme.toggleDarkMode() == false);
        REQUIRE(theme.toggleDarkMode() == true);
    }

    SECTION("Toggle starting from dark mode") {
        AppTheme theme("Dark", true, "red");
        REQUIRE(theme.toggleDarkMode() == false);
    }
}