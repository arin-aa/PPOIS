#include <catch2/catch_test_macros.hpp>
#include "ContentCatalog.h"
#include "MediaLibrary.h"
#include "Track.h"

TEST_CASE("ContentCatalog: Indexing and Searching") {
    Track t1(1, "Hello World", 1, 1, 1000, nullptr);
    Track t2(2, "Goodbye World", 1, 1, 1000, nullptr);
    Track t3(3, "Hello Again", 1, 1, 1000, nullptr);
    
    MediaLibrary lib({&t1, &t2, &t3});
    ContentCatalog catalog(&lib);

    SECTION("rebuildIndex returns count of tracks indexed") {
        REQUIRE(catalog.rebuildIndex() == 3);
    }

    SECTION("searchByTitle returns empty if query is empty") {
        catalog.rebuildIndex();
        REQUIRE(catalog.searchByTitle("").empty());
    }

    SECTION("searchByTitle returns matching tracks") {
        catalog.rebuildIndex();
        
        auto res = catalog.searchByTitle("hello");
        REQUIRE(res.size() == 2); 
        REQUIRE(res[0] == &t1);
        REQUIRE(res[1] == &t3);

        auto res2 = catalog.searchByTitle("goodbye");
        REQUIRE(res2.size() == 1); 
        REQUIRE(res2[0] == &t2);
    }

    SECTION("searchByTitle returns empty if no match") {
        catalog.rebuildIndex();
        REQUIRE(catalog.searchByTitle("nothing").empty());
    }
    
    SECTION("getLibrary returns the correct pointer") {
        REQUIRE(catalog.getLibrary() == &lib);
    }
}