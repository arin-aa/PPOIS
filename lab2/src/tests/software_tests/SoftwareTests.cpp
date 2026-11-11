#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Software.h"

TEST_CASE("Software: Installation") {
    Software app("TestApp", 1024); 

    SECTION("Install with enough space") {
        REQUIRE(app.install(5) == 2);
    }

    SECTION("Install with not enough space throws") {
        REQUIRE_THROWS_AS(app.install(1), DiskFullException); 
    }
}