#include <catch2/catch_test_macros.hpp>
#include "SyncService.h"
#include "CloudStorage.h"

TEST_CASE("SyncService: Integration with CloudStorage") {
    CloudStorage cloud("http://api", "token");
    SyncService service(&cloud);

    SECTION("First sync uploads local version") {
        // До этого облако пустое (NEVER_SYNCED)
        long long result = service.sync("playlists", 100, "newest");
        
        REQUIRE(result == 100);
        REQUIRE(cloud.getLastSyncAt() == 100); // Загрузилось
    }

    SECTION("Sync without conflict updates nothing") {
        service.sync("playlists", 100, "newest"); // Первая загрузка
        
        // Синхронизируем ту же версию
        long long result = service.sync("playlists", 100, "newest");
        
        REQUIRE(result == 100);
        REQUIRE(cloud.getLastSyncAt() == 100);
    }

    SECTION("Sync with conflict resolves and uploads if local is newer") {
        service.sync("playlists", 100, "newest"); // Облако: 100
        
        // Локальная версия 200, облако 100. По стратегии newest выбираем 200.
        long long result = service.sync("playlists", 200, "newest");
        
        REQUIRE(result == 200);
        REQUIRE(cloud.getLastSyncAt() == 200); // Обновилось
    }

    SECTION("Sync with conflict resolves but does not upload if remote is newer") {
        service.sync("playlists", 500, "newest"); // Облако: 500
        
        // Локальная версия 100, облако 500. По стратегии newest выбираем 500.
        long long result = service.sync("playlists", 100, "newest");
        
        REQUIRE(result == 500);
        REQUIRE(cloud.getLastSyncAt() == 500); // Осталось 500, ничего не загружали
    }
}