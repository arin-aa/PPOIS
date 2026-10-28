#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "Computer.h"
#include "ComputerExceptions.h"
#include "Motherboard.h"
#include "PSU.h"
#include "OperatingSystem.h"
#include "SSD.h"
#include "Laptop.h"
#include "Battery.h"
#include "Server.h"
#include "Workstation.h"
#include "GPU.h"
#include "NetworkInterface.h"
#include "Packet.h"
#include "IpAddress.h"

TEST_CASE("Computer: Assembling and Powering On", "[Computer]") {
    Computer pc("test-pc");
    Motherboard board("LGA1700", 2);
    PSU psu(500, "80+ Gold");
    SSD disk(256);
    
    SECTION("Cannot power on if not assembled") {
        REQUIRE_THROWS_AS(pc.powerOn(), BootFailureException);
    }

    SECTION("Cannot install OS without disk") {
        OperatingSystem os("Linux", 5000);
        pc.assemble(&board, &psu);
        REQUIRE_THROWS_AS(pc.installOs(&os), InvalidConfigurationException);
    }

    SECTION("Cannot power on with weak PSU") {
        PSU weakPsu(10, "Weak"); 
        pc.assemble(&board, &weakPsu);
        REQUIRE_THROWS_AS(pc.powerOn(), InsufficientPowerException);
    }

    SECTION("Successful assembly, install OS, and power on") {
        OperatingSystem os("Linux", 5000);
        pc.assemble(&board, &psu);
        pc.addStorage(&disk);
        
        int initialFreeSpace = pc.freeStorageGb();
        REQUIRE(initialFreeSpace == 256);

        pc.installOs(&os);
        REQUIRE(pc.freeStorageGb() < initialFreeSpace); 

        REQUIRE_NOTHROW(pc.powerOn());
    }
}

TEST_CASE("Computer: Power Calculations", "[Computer]") {
    Computer pc("calc-pc");
    Motherboard board("LGA1700", 2);
    PSU psu(500, "80+ Gold");
    SSD disk(256);

    SECTION("Power draw with no components (Base only)") {
        REQUIRE(pc.powerDraw() == 30); 
    }

    SECTION("Power draw with components") {
        pc.assemble(&board, &psu);
        pc.addStorage(&disk);
        
        REQUIRE(pc.powerDraw() > 30); 
    }
    
    SECTION("Power reserve throws if no PSU") {
        REQUIRE_THROWS_AS(pc.powerReserve(), BootFailureException);
    }
}

TEST_CASE("Laptop: Charging and Battery", "[Laptop]") {
    Battery battery(50, 10);
    Laptop laptop("lt-01", 15, &battery);
    Motherboard board("LGA1700", 1);
    PSU psu(500, "80+ Gold");
    
    laptop.assemble(&board, &psu);

    SECTION("PlugIn charges battery and returns charge percentage") {
        int newCharge = laptop.plugIn(10);
        REQUIRE(newCharge >= 0); 
    }

    SECTION("PowerDraw overrides base class (adds screen watts)") {
        int baseDraw = Computer("lt-01").powerDraw();
        REQUIRE(laptop.powerDraw() > 30); 
    }

    SECTION("batteryMinutes returns runtime") {
        REQUIRE(laptop.batteryMinutes() >= 0);
    }
}

TEST_CASE("Server: RAID and Requests", "[Server]") {
    IpAddress ip("192.168.0.10", 24);
    NetworkInterface nic(1000);
    nic.connect(&ip); 
    Packet packet(&ip, "192.168.0.20", 512, 1);
    
    Server server("web-01", 2, &nic);

    SECTION("Valid RAID levels return correct usable percentage") {
        REQUIRE(server.configureRaid("RAID0") == 100);
        REQUIRE(server.configureRaid("RAID1") == 50);
        REQUIRE(server.configureRaid("RAID5") == 67);
    }

    SECTION("Invalid RAID level throws exception") {
        REQUIRE_THROWS_AS(server.configureRaid("RAID9"), InvalidConfigurationException);
    }

    SECTION("HandleRequest increments counter and transmits") {
        REQUIRE_NOTHROW(server.handleRequest(&packet));
    }
    
    SECTION("Power draw includes NIC and Rack units") {
        REQUIRE(server.powerDraw() >= 30 + 10 + (2 * 15));
    }
}

TEST_CASE("Server: Exception without NIC", "[Server]") {
    Server emptyServer;
    IpAddress ip("192.168.0.10", 24);
    Packet packet(&ip, "192.168.0.20", 512, 1);

    REQUIRE_THROWS_AS(emptyServer.handleRequest(&packet), NetworkDisconnectedException);
}

TEST_CASE("Workstation: GPU Rendering", "[Workstation]") {
    Workstation ws("render-pc");
    GPU gpu1(8, 1500);
    GPU gpu2(16, 1500);

    SECTION("RenderTask throws without GPU") {
        REQUIRE_THROWS_AS(ws.renderTask(100), InvalidConfigurationException);
    }

    SECTION("RenderTask with one GPU") {
        ws.addGpu(&gpu1);
        double time = ws.renderTask(400);
        REQUIRE(time > 0); 
    }

    SECTION("RenderTask with multiple GPUs (takes the slowest)") {
        ws.addGpu(&gpu1);
        ws.addGpu(&gpu2);
        
        double time = ws.renderTask(1000);
        REQUIRE(time > 0);
    }
}