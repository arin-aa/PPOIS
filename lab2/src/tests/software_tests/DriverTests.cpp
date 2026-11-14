#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Driver.h"
#include "Component.h"

TEST_CASE("Driver: Binding and Loading") {
    Driver gpuDriver("nvidia-drv", "GPU", true);   
    Driver rogueDriver("rogue", "GPU", false);    
    
    Component gpu("GPU", "Nvidia", 200);
    Component cpu("CPU", "Intel", 65);

    SECTION("Bind to matching component") {
        REQUIRE_NOTHROW(gpuDriver.bind(&gpu));
    }

    SECTION("Bind to mismatching component throws") {
        REQUIRE_THROWS_AS(gpuDriver.bind(&cpu), DriverNotFoundException);
    }

    SECTION("Load signed driver") {
        REQUIRE_NOTHROW(gpuDriver.load());
    }

    SECTION("Load unsigned driver throws") {
        REQUIRE_THROWS_AS(rogueDriver.load(), BootFailureException);
    }
}