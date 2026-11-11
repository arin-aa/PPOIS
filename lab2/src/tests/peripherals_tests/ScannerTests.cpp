#include <catch2/catch_test_macros.hpp>

#include "Scanner.h"
#include "Port.h"
#include "Cable.h"

static Port* createWorkingPort(Cable** outCable) {
    *outCable = new Cable("USB", 1.0, 500); 
    Port* port = new Port("USB", 480);         
    port->plug(*outCable);
    return port;
}

TEST_CASE("Scanner: Scan pages") {
    Cable* cable = nullptr;
    Port* port = createWorkingPort(&cable);

    Scanner scn(1200, 24);
    scn.connectTo(port);
    REQUIRE(scn.scanPages(2) == 57);

    delete port;
    delete cable;
}