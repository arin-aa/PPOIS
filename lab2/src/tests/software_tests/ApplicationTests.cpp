#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Application.h"

TEST_CASE("Application: License and Launch") {
    Application app("Blender", 2000, 4096, "KEY-123"); 

    SECTION("Check license branches") {
        REQUIRE(app.checkLicense("KEY-123") == true);
        REQUIRE(app.checkLicense("WRONG") == false);
        
        Application noLicenseApp("Notepad", 10, 128, "");
        REQUIRE(noLicenseApp.checkLicense("") == false);
        REQUIRE(noLicenseApp.checkLicense("ANY") == false);
    }

    SECTION("Launch without installation throws") {
        REQUIRE_THROWS_AS(app.launch(8192), InvalidConfigurationException);
    }

    SECTION("Launch with insufficient RAM throws") {
        app.install(10); 
        REQUIRE_THROWS_AS(app.launch(2048), MemoryOverflowException); 
    }

    SECTION("Successful launch") {
        app.install(10);
        REQUIRE(app.launch(8192) == 4096);
    }
}