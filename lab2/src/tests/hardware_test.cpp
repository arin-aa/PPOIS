#include <catch2/catch_test_macros.hpp>
#include "ComputerExceptions.h"

#include "Component.h"
#include "CPU.h"
#include "RAM.h"
#include "Motherboard.h"
#include "GPU.h"
#include "Storage.h"
#include "SSD.h"
#include "HDD.h"
#include "NVMe.h"
#include "PSU.h"
#include "Case.h"
#include "Fan.h"
#include "Battery.h"
#include "Cable.h"
#include "Port.h"
#include "Cooler.h"
#include "Radiator.h"
#include "Sensor.h"
#include "PowerConnector.h"

TEST_CASE("Component: Basic behavior") {
    Component comp("CPU", "Intel", 100);

    SECTION("isNamed checks name and manufacturer") {
        REQUIRE(comp.isNamed("CPU") == true);
        REQUIRE(comp.isNamed("Intel") == true);
        REQUIRE(comp.isNamed("AMD") == false);
    }

    SECTION("draw calculates load") {
        REQUIRE(comp.draw(50) == 50); 
        REQUIRE(comp.draw(0) == 0);
    }
}

TEST_CASE("Cooler and Radiator") {
    SECTION("Cooler headroom can be negative or positive") {
        Cooler cooler("Noctua", 150);
        REQUIRE(cooler.headroom(100) == 50);
        REQUIRE(cooler.headroom(200) == -50);
    }

    SECTION("Radiator refill caps at capacity") {
        Radiator rad(100, 200); 
        REQUIRE(rad.refill(150) == 150); 
        REQUIRE(rad.refill(100) == 200); 
    }
}

TEST_CASE("Fan: RPM limits and Airflow") {
    Fan fan(120, 1000);

    SECTION("Airflow calculation") {
        REQUIRE(fan.airflow() == 1200); 
    }

    SECTION("accelerate clamps RPM") {
        REQUIRE(fan.accelerate(-2000) == 0);       
        REQUIRE(fan.accelerate(10000) == 2000);    
        REQUIRE(fan.accelerate(-1000) == 1000);   
    }
}

TEST_CASE("CPU: Load, Throttling and Sockets") {
    Sensor sensor(80.0);
    CPU cpu("LGA1700", 8, 3.0, &sensor);

    SECTION("Invalid load throws") {
        REQUIRE_THROWS_AS(cpu.runLoad(-1), InvalidConfigurationException);
        REQUIRE_THROWS_AS(cpu.runLoad(101), InvalidConfigurationException);
    }

    SECTION("Throttling reduces frequency if load > 95") {
        cpu.runLoad(99); 
        REQUIRE_NOTHROW(cpu.runLoad(99));
    }

    SECTION("Overheating throws") {
        sensor.measure(100.0); 
        REQUIRE_THROWS_AS(cpu.runLoad(50), OverheatingException);
    }

    SECTION("Socket mismatch throws") {
        REQUIRE_THROWS_AS(cpu.checkSocket("AM5"), IncompatibleSocketException);
        REQUIRE_NOTHROW(cpu.checkSocket("LGA1700"));
    }
}

TEST_CASE("RAM: Allocation and Limits") {
    RAM ram(16, 3200);

    SECTION("Free space") {
        REQUIRE(ram.freeGb() == 16);
    }

    SECTION("Allocate successful") {
        REQUIRE(ram.allocate(8) > 0); 
        REQUIRE(ram.freeGb() == 8);
    }

    SECTION("Allocate overflow throws") {
        REQUIRE_THROWS_AS(ram.allocate(17), MemoryOverflowException);
    }
}

TEST_CASE("Motherboard: CPU and RAM installation") {
    Motherboard board("LGA1700", 2);
    CPU cpu("LGA1700", 8, 3.0);
    RAM ram1(16, 3200);
    RAM ram2(8, 3200);

    SECTION("Install valid CPU") {
        REQUIRE_NOTHROW(board.installCpu(&cpu));
    }

    SECTION("Install RAM up to capacity") {
        board.installRam(&ram1);
        board.installRam(&ram2);
        REQUIRE(board.freeRamGb() == 24);
        
        RAM ram3(8, 3200);
        REQUIRE_THROWS_AS(board.installRam(&ram3), InvalidConfigurationException);
    }
}

TEST_CASE("Storage: Base write, erase, life") {
    Storage disk("HDD", 100);

    SECTION("Write successful") {
        REQUIRE_NOTHROW(disk.write(50));
        REQUIRE(disk.freeSpace() == 50);
    }

    SECTION("Write overflow throws") {
        REQUIRE_THROWS_AS(disk.write(101), DiskFullException);
    }

    SECTION("Erase branches") {
        disk.write(10);
        REQUIRE(disk.erase(5) == 5);   
        REQUIRE(disk.erase(10) == 5);  
        REQUIRE(disk.lifeLeft() == 100);
    }
}

TEST_CASE("SSD: Trim and Wear") {
    SSD ssd(256);

    SECTION("Trim reduces used space") {
        ssd.write(100);
        REQUIRE(ssd.trim() > 0); 
    }

    SECTION("Life left calculates wear") {
        for(int i=0; i<100; i++) ssd.write(1);
        REQUIRE(ssd.lifeLeft() == 0); 
    }
}

TEST_CASE("HDD: Defragmentation and Wear") {
    SECTION("Defragment resets fragmentation and adds bad sectors") {
        HDD hdd(1000, 7200, 50); 
        REQUIRE(hdd.defragment() > 0);
        REQUIRE(hdd.defragment() == 0);
    }

    SECTION("Life left goes negative branch") {
        HDD hdd(1000, 7200, 100); 
        hdd.defragment(); 
        REQUIRE(hdd.lifeLeft() == 75);
    }
}

TEST_CASE("NVMe: Read speed cap") {
    SECTION("Queue depth below max") {
        NVMe nvme(512, 4, 16);
        REQUIRE(nvme.readSpeed() == 1800);
    }

    SECTION("Queue depth above max (caps at 32)") {
        NVMe nvme(512, 4, 64);
        REQUIRE(nvme.readSpeed() == 3600);
    }
}

TEST_CASE("PSU: Reserve and Wall Draw") {
    SECTION("Reserve is positive/negative") {
        PSU psu(500, "80+ Gold");
        REQUIRE(psu.reserve(400) == 100);
        REQUIRE(psu.reserve(600) == -100);
    }

    SECTION("Wall Draw calculates efficiency") {
        PSU gold(500, "80+ Gold"); 
        PSU base(500, "80+");      
        
        REQUIRE(gold.wallDraw(450) == 500); 
        REQUIRE(base.wallDraw(400) == 500); 
    }
}

TEST_CASE("Battery: Charge and Runtime") {
    Battery bat(100, 50);

    SECTION("Charge caps at 100") {
        REQUIRE(bat.charge(20) == 70);
        REQUIRE(bat.charge(50) == 100); 
    }

    SECTION("Runtime zero watts") {
        REQUIRE(bat.runtimeMinutes(0) == 0);
    }

    SECTION("Runtime normal") {
        REQUIRE(bat.runtimeMinutes(50) == 60);
    }
}

TEST_CASE("Case: Fans and Dust") {
    Case pcCase(2); 
    Fan fan1(120, 1000);
    Fan fan2(120, 1000);
    Fan fan3(120, 1000);

    SECTION("Add fan up to limit, third throws") {
        pcCase.addFan(&fan1);
        pcCase.addFan(&fan2);
        REQUIRE_THROWS_AS(pcCase.addFan(&fan3), InvalidConfigurationException);
    }

    SECTION("Airflow with dust reduction") {
        Case bigCase(20);
        for(int i=0; i<11; i++) {
            bigCase.addFan(&fan1);
        }
        REQUIRE(bigCase.totalAirflow() == 6600); 
    }
}

TEST_CASE("Cable: Match and Speed Loss") {
    SECTION("Match throws on mismatch") {
        Cable cable("USB", 1.0, 500);
        REQUIRE_NOTHROW(cable.match("USB"));
        REQUIRE_THROWS_AS(cable.match("HDMI"), InvalidConfigurationException);
    }

    SECTION("Effective Mbps") {
        Cable fastCable("USB", 2.0, 500); 
        Cable slowCable("USB", 20.0, 500); 
        
        REQUIRE(fastCable.effectiveMbps() == 400);
        REQUIRE(slowCable.effectiveMbps() == 0);
    }
}

TEST_CASE("Port: Plug and Throughput") {
    Port port("USB", 480);
    Cable slowCable("USB", 2.0, 400); 
    Cable fastCable("USB", 1.0, 1000); 

    SECTION("No cable throws") {
        REQUIRE_THROWS_AS(port.throughput(), PeripheralNotRespondingException);
    }

    SECTION("Throughput limits by cable or port") {
        port.plug(&slowCable);
        REQUIRE(port.throughput() == 300); 

        port.plug(&fastCable);
        REQUIRE(port.throughput() == 480);
    }
}

TEST_CASE("PowerConnector: Attach") {
    PowerConnector conn(24);
    REQUIRE(conn.attach() == 24);
    REQUIRE_THROWS_AS(conn.attach(), InvalidConfigurationException);
}

TEST_CASE("GPU: Render Time and VRAM Limits") {
    GPU gpu(8, 1000); 

    SECTION("Render overflow throws") {
        REQUIRE_THROWS_AS(gpu.renderTime(801), MemoryOverflowException);
    }

    SECTION("Render normal") {
        REQUIRE(gpu.renderTime(100) == 100.0);
    }
}