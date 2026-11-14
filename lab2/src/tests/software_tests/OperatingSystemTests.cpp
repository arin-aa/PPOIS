#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"
#include "OperatingSystem.h"
#include "Process.h"
#include "Application.h"
#include "Driver.h"

TEST_CASE("OperatingSystem: Booting and Processes") {
    OperatingSystem os("Linux", 5000);
    Application app("Blender", 2000, 1000, "KEY");
    app.install(10);
    Process proc(&app);
    
    SECTION("Boot uninstalled OS throws") {
        REQUIRE_THROWS_AS(os.boot(), BootFailureException);
    }

    SECTION("Boot with unsigned driver throws") {
        os.install(10);
        Driver rogue("rogue", "GPU", false);
        os.addDriver(&rogue);
        REQUIRE_THROWS_AS(os.boot(), BootFailureException);
    }

    SECTION("Start process on non-booted OS throws") {
        os.install(10);
        REQUIRE_THROWS_AS(os.startProcess(&proc, 4096), BootFailureException);
    }

    SECTION("Successful boot and start process") {
        os.install(10);
        Driver good("nvidia", "GPU", true);
        os.addDriver(&good);
        
        REQUIRE_NOTHROW(os.boot());
        
        int pid = os.startProcess(&proc, 4096);
        REQUIRE(pid == 1000);
    }

    SECTION("Kill process branches") {
        os.install(10);
        os.boot();
        
        REQUIRE(os.killProcess(999) == -1);
        REQUIRE(os.killProcess(1005) == -1);

        int pid = os.startProcess(&proc, 4096); 
        int freedMb = os.killProcess(pid);
        
        REQUIRE(freedMb == 1000); 
    }
}