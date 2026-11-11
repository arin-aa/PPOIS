#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include "DownloadManager.h"
#include "MusicPlayerExceptions.h"

TEST_CASE("DownloadManager: Start and Cancel") {
    DownloadManager manager(2); // max 2 concurrent

    SECTION("Start throws on empty URL") {
        REQUIRE_THROWS_AS(manager.start(1, ""), DownloadException);
    }

    SECTION("Start queues when limit reached") {
        REQUIRE(manager.start(1, "url1") == true);
        REQUIRE(manager.start(2, "url2") == true);
        // Лимит 2. Третий встает в очередь.
        REQUIRE(manager.start(3, "url3") == false);
    }

    SECTION("Cancel removes from queue") {
        manager.start(1, "url");
        manager.start(2, "url");
        manager.start(3, "url"); // В очереди

        REQUIRE_NOTHROW(manager.cancel(3)); // Удаляет 3 из очереди
        // Теперь очередь пуста. Отмена несуществующего (при active>0) уменьшит счетчик.
        REQUIRE_NOTHROW(manager.cancel(99)); 
    }

    SECTION("Cancel throws if nothing is active") {
        REQUIRE_THROWS_AS(manager.cancel(1), TrackNotFoundException);
    }

    SECTION("Cancel pops from queue if active count > 0 and queue is not empty") {
        manager.start(1, "url");
        manager.start(2, "url");
        manager.start(3, "url"); // В очереди
        manager.start(4, "url"); // В очереди [3, 4]
        
        manager.cancel(99); // Удаляет первый из очереди (3)
        // Проверим, что 3 больше нет в очереди (отмена 4 удалит 4, а отмена 3 теперь удалит пустоту и уменьшит activeCount)
        REQUIRE_NOTHROW(manager.cancel(4));
    }
}