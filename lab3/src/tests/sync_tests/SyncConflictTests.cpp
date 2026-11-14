#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "SyncConflict.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("SyncConflict: Resolution Strategies") {
    SyncConflict conflict("playlists", 100, 200);

    SECTION("Local strategy returns local version") {
        REQUIRE(conflict.applyResolution("local") == 100);
    }

    SECTION("Remote strategy returns remote version") {
        REQUIRE(conflict.applyResolution("remote") == 200);
    }

    SECTION("Newest strategy returns max of two") {
        REQUIRE(conflict.applyResolution("newest") == 200);
        
        SyncConflict localNewer("playlists", 300, 200);
        REQUIRE(localNewer.applyResolution("newest") == 300);
    }

    SECTION("Unknown strategy throws") {
        REQUIRE_THROWS_AS(conflict.applyResolution("random"), SyncException);
    }
}