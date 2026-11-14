#include <catch2/catch_test_macros.hpp>
#include "Fan.h"

TEST_CASE("Fan: RPM limits and Airflow") {
    Fan fan(120, 1000);

    SECTION("Airflow calculation") {
        REQUIRE(fan.airflow() == 1200); 
    }

    SECTION("accelerate clamps RPM") {
        REQUIRE(fan.accelerate(-2000) == 0);       
        REQUIRE(fan.accelerate(10000) == 2000);    
        REQUIRE(fan.accelerate(-1000) == 1000);   
    }
}