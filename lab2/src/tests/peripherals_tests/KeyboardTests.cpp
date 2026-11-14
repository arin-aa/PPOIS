#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Keyboard.h"
#include "Port.h"
#include "Cable.h"

static Port* createWorkingPort(Cable** outCable) {
    *outCable = new Cable("USB", 1.0, 500); 
    Port* port = new Port("USB", 480);         
    port->plug(*outCable);
    return port;
}

TEST_CASE("Keyboard: Layouts and Presses") {
    Keyboard kb("EN");
    Cable* cable = nullptr;
    Port* port = createWorkingPort(&cable);
    kb.connectTo(port);

    SECTION("Switch valid layouts") {
        REQUIRE_NOTHROW(kb.switchLayout("RU"));
        REQUIRE_NOTHROW(kb.switchLayout("DE"));
    }

    SECTION("Switch invalid layout throws") {
        REQUIRE_THROWS_AS(kb.switchLayout("FR"), InvalidConfigurationException);
    }

    SECTION("Press keys") {
        REQUIRE(kb.press(5) == 5);
        REQUIRE(kb.press(3) == 8);
    }
    
    delete port;
    delete cable;
}