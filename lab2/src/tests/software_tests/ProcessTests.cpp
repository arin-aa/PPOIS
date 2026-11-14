#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "Process.h"
#include "Application.h"

TEST_CASE("Process: Start and Terminate") {
    Application app("Blender", 2000, 1000, "KEY"); 
    app.install(10);
    Process proc(&app);

    SECTION("Terminate a process that hasn't started (State: NEW)") {
        REQUIRE(proc.terminate() == 0);
    }

    SECTION("Start and then terminate") {
        REQUIRE(proc.start(2000) == 1000);
        REQUIRE(proc.terminate() == 1000);
        REQUIRE(proc.terminate() == 0);
    }
}