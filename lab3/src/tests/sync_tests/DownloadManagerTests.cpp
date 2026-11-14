#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "DownloadManager.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("DownloadManager: Start and Cancel") {
    DownloadManager manager(2); 

    SECTION("Start throws on empty URL") {
        REQUIRE_THROWS_AS(manager.start(1, ""), DownloadException);
    }

    SECTION("Start queues when limit reached") {
        REQUIRE(manager.start(1, "url1") == true);
        REQUIRE(manager.start(2, "url2") == true);
        REQUIRE(manager.start(3, "url3") == false);
    }

    SECTION("Cancel removes from queue") {
        manager.start(1, "url");
        manager.start(2, "url");
        manager.start(3, "url"); 

        REQUIRE_NOTHROW(manager.cancel(3)); 
        REQUIRE_NOTHROW(manager.cancel(99)); 
    }

    SECTION("Cancel throws if nothing is active") {
        REQUIRE_THROWS_AS(manager.cancel(1), TrackNotFoundException);
    }

    SECTION("Cancel pops from queue if active count > 0 and queue is not empty") {
        manager.start(1, "url");
        manager.start(2, "url");
        manager.start(3, "url"); 
        manager.start(4, "url"); 
        
        manager.cancel(99); 
        REQUIRE_NOTHROW(manager.cancel(4));
    }
}