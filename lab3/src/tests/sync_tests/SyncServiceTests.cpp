#include <catch2/catch_test_macros.hpp>
#include "SyncService.h"
#include "CloudStorage.h"

TEST_CASE("SyncService: Integration with CloudStorage") {
    CloudStorage cloud("http://api", "token");
    SyncService service(&cloud);

    SECTION("First sync uploads local version") {
        long long result = service.sync("playlists", 100, "newest");
        
        REQUIRE(result == 100);
        REQUIRE(cloud.getLastSyncAt() == 100); 
    }

    SECTION("Sync without conflict updates nothing") {
        service.sync("playlists", 100, "newest"); 
        long long result = service.sync("playlists", 100, "newest");
        
        REQUIRE(result == 100);
        REQUIRE(cloud.getLastSyncAt() == 100);
    }

    SECTION("Sync with conflict resolves and uploads if local is newer") {
        service.sync("playlists", 100, "newest"); 
        
        long long result = service.sync("playlists", 200, "newest");
        
        REQUIRE(result == 200);
        REQUIRE(cloud.getLastSyncAt() == 200); 
    }

    SECTION("Sync with conflict resolves but does not upload if remote is newer") {
        service.sync("playlists", 500, "newest"); 
        
        long long result = service.sync("playlists", 100, "newest");
        
        REQUIRE(result == 500);
        REQUIRE(cloud.getLastSyncAt() == 500); 
    }
}