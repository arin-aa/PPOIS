#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Peripheral.h"
#include "Keyboard.h"
#include "Port.h"
#include "Cable.h"

static Port* createWorkingPort(Cable** outCable) {
    *outCable = new Cable("USB", 1.0, 500); 
    Port* port = new Port("USB", 480);         
    port->plug(*outCable);
    return port;
}

TEST_CASE("Peripheral: Connection and Ping") {
    Keyboard kb("EN");
    Cable* cable = nullptr;
    Port* validPort = createWorkingPort(&cable);
    Port emptyPort("USB", 480); 

    SECTION("Ping throws if not connected") {
        REQUIRE_THROWS_AS(kb.ping(), PeripheralNotRespondingException);
    }

    SECTION("ConnectTo throws if port has no cable") {
        REQUIRE_THROWS_AS(kb.connectTo(&emptyPort), PeripheralNotRespondingException);
    }

    SECTION("Successful connection and ping calculation") {
        kb.connectTo(validPort);
        REQUIRE(kb.ping() == 322); 
    }
  
    delete validPort;
    delete cable;
}