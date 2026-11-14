#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "CompatibilityChecker.h"

TEST_CASE("CompatibilityChecker: Power checking") {
    SECTION("Normal mode (not strict)") {
        CompatibilityChecker checker(false, 100);
        REQUIRE(checker.checkPower(500, 450) == 50);
    }

    SECTION("Strict mode: sufficient reserve") {
        CompatibilityChecker checker(true, 100);
        REQUIRE(checker.checkPower(500, 350) == 150);
    }

    SECTION("Strict mode: insufficient reserve throws") {
        CompatibilityChecker checker(true, 100);
        REQUIRE_THROWS_AS(checker.checkPower(500, 450), InsufficientPowerException);
    }
}