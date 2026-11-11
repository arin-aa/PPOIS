 #include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Mouse.h"
#include "Port.h"
#include "Cable.h"

static Port* createWorkingPort(Cable** outCable) {
    *outCable = new Cable("USB", 1.0, 500); 
    Port* port = new Port("USB", 480);         
    port->plug(*outCable);
    return port;
}

TEST_CASE("Mouse: DPI and Clicks") {
    Mouse mouse(800);
    Cable* cable = nullptr;
    Port* port = createWorkingPort(&cable);
    mouse.connectTo(port);

    SECTION("Valid DPI change") {
        REQUIRE(mouse.changeDpi(16000) == 16000);
        REQUIRE(mouse.changeDpi(100) == 100);
    }

    SECTION("DPI out of bounds throws") {
        REQUIRE_THROWS_AS(mouse.changeDpi(99), InvalidConfigurationException);
        REQUIRE_THROWS_AS(mouse.changeDpi(16001), InvalidConfigurationException);
    }

    SECTION("Clicks increment") {
        REQUIRE(mouse.click() == 1);
        REQUIRE(mouse.click() == 2);
    }
    
    delete port;
    delete cable;
}