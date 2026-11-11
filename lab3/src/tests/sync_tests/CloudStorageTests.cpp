#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "CloudStorage.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("CloudStorage: Upload and Download") {
    CloudStorage cloud("http://api", "token");
    CloudStorage guest("http://api", "");

    SECTION("Operations without token throw SyncException") {
        REQUIRE_THROWS_AS(guest.upload("playlists", 100), SyncException);
        REQUIRE_THROWS_AS(guest.download("playlists"), SyncException);
    }

    SECTION("Download before any upload throws SyncException") {
        REQUIRE_THROWS_AS(cloud.download("playlists"), SyncException);
    }

    SECTION("Upload updates lastSyncAt and allows download") {
        REQUIRE(cloud.getLastSyncAt() == 0); 
        
        cloud.upload("playlists", 500);
        REQUIRE(cloud.getLastSyncAt() == 500);
        REQUIRE(cloud.download("playlists") == 500);
    }
}