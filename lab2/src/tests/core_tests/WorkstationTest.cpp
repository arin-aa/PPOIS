#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "Workstation.h"
#include "ComputerExceptions.h"
#include "GPU.h"

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