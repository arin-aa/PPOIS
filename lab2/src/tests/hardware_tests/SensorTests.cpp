#include <catch2/catch_test_macros.hpp>
#include "Sensor.h"

TEST_CASE("Sensor: Measure and Margin") {
    Sensor sensor(80.0);

    SECTION("Margin before any measurement equals threshold") {
        REQUIRE(sensor.margin() == 80.0);
    }

    SECTION("Measure computes running average") {
        sensor.measure(60.0);
        REQUIRE(sensor.margin() == 20.0);

        sensor.measure(80.0);
        REQUIRE(sensor.margin() == 10.0);

        sensor.measure(100.0);
        REQUIRE(sensor.margin() == 0.0);
    }
}