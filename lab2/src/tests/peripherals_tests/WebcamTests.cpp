#include <catch2/catch_test_macros.hpp>

#include "Webcam.h"
#include "Port.h"
#include "Cable.h"

static Port* createWorkingPort(Cable** outCable) {
    *outCable = new Cable("USB", 1.0, 500); 
    Port* port = new Port("USB", 480);         
    port->plug(*outCable);
    return port;
}

TEST_CASE("Webcam: Record video") {
    Cable* cable = nullptr;
    Port* port = createWorkingPort(&cable);

    Webcam cam(1080, 30);
    cam.connectTo(port);
    REQUIRE(cam.record(10) == 32);

    delete port;
    delete cable;
}