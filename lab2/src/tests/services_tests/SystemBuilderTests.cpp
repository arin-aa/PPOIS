#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "SystemBuilder.h"
#include "CompatibilityChecker.h"

TEST_CASE("SystemBuilder: Budget and Power Calculations") {
    CompatibilityChecker checker(true, 100); 
    SystemBuilder builder(1000, &checker);   

    SECTION("Add parts within budget") {
        builder.addPart(100, 500); 
        builder.addPart(50, 400);  
        REQUIRE(builder.recommendedPsu() == 250);
    }

    SECTION("Add parts exceeding budget throws") {
        builder.addPart(100, 500);
        REQUIRE_THROWS_AS(builder.addPart(50, 600), InvalidConfigurationException);
    }

    SECTION("Power margin calculation") {
        builder.addPart(100, 500);
        REQUIRE(builder.powerMargin(300) == 200);
        REQUIRE_THROWS_AS(builder.powerMargin(150), InsufficientPowerException);
    }
}