#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "ComputerExceptions.h"

#include "Software.h"
#include "Application.h"
#include "Driver.h"
#include "File.h"
#include "Folder.h"
#include "OperatingSystem.h"
#include "Process.h"

#include "Component.h"

TEST_CASE("Software: Installation") {
    Software app("TestApp", 1024); 

    SECTION("Install with enough space") {
        REQUIRE(app.install(5) == 2);
    }

    SECTION("Install with not enough space throws") {
        REQUIRE_THROWS_AS(app.install(1), DiskFullException); 
    }
}

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

TEST_CASE("File: Content and Size") {
    File normalFile("notes.txt", 10, false);
    File lockedFile("locked.txt", 5, true);

    SECTION("Append to normal file") {
        REQUIRE_NOTHROW(normalFile.append("Hello"));
        REQUIRE(normalFile.pageCount() == 1);
    }

    SECTION("Append to read-only file throws") {
        REQUIRE_THROWS_AS(lockedFile.append("text"), UnauthorizedAccessException);
    }

    SECTION("Page count for large file") {
        normalFile.append(std::string(1200, 'x'));
        REQUIRE(normalFile.pageCount() == 3);
    }

    SECTION("Fit into folder space") {
        REQUIRE(normalFile.fitInto(20) == 10); 
        REQUIRE_THROWS_AS(normalFile.fitInto(5), DiskFullException);
    }
}

TEST_CASE("Folder: Adding Files and Pages") {
    Folder folder(15); 
    File file1("a.txt", 5, false);
    File file2("b.txt", 20, false);

    SECTION("Add file that fits") {
        REQUIRE_NOTHROW(folder.addFile(&file1));
    }

    SECTION("Add file that does not fit throws") {
        REQUIRE_THROWS_AS(folder.addFile(&file2), DiskFullException);
    }

    SECTION("Total pages sums correctly") {
        file1.append(std::string(600, 'a')); 
        folder.addFile(&file1);
        REQUIRE(folder.totalPages() == 2);
    }
}

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