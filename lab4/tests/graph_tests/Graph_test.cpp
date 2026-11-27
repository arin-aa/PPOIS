#include <catch2/catch_test_macros.hpp>
#include "Graph.hpp"

namespace{
using G = Graph<int>;
}

TEST_CASE("Graph.hpp: comparison operators") {
    SECTION("Equal graphs") {
        G a;
        a.addVertex(1); a.addVertex(2); a.addVertex(3);
        a.addEdge(1,2); a.addEdge(2,3);

        G b;
        b.addVertex(3); b.addVertex(2); b.addVertex(1);
        b.addEdge(3,2); b.addEdge(2,1);

        REQUIRE(a==b);
        REQUIRE_FALSE(a!=b);
        REQUIRE_FALSE(a<b);
        REQUIRE_FALSE(a>b);
    }

    SECTION("Graph with fewer vertices is smaller") {
        G small;
        small.addVertex(1);
        G big;
        big.addVertex(1);
        big.addVertex(2);

        REQUIRE(small<big);
        REQUIRE(big>small);
    }

    SECTION("Same sizes, different vertices") {
        G a;
        a.addVertex(1); a.addVertex(2);
        G b;
        b.addVertex(1); b.addVertex(3);

        REQUIRE(a<b);
        REQUIRE(a!=b);
    }

    SECTION("Same vertices, different edges") {
        G a;
        a.addVertex(1); a.addVertex(2); a.addVertex(3);
        a.addEdge(1,2);
        G b;
        b.addVertex(1); b.addVertex(2); b.addVertex(3);
        b.addEdge(2,3);

        REQUIRE(a<b);
    }
}

TEST_CASE("Graph.hpp: iterator accessors on an empty graph") {
    G g;
    const G& cg=g;

    REQUIRE(g.vBegin()==g.vEnd());
    REQUIRE(g.rvBegin()==g.rvEnd());
}

TEST_CASE("Graph.hpp: iterator accessors for a vertex") {
    G g;
    g.addVertex(1);
    const G& cg=g;

    REQUIRE(cg.ciBegin(1)==cg.ciEnd(1));
    REQUIRE(cg.criBegin(1)==cg.criEnd(1));

    REQUIRE(g.aBegin(1)==g.aEnd(1));
    REQUIRE(g.raBegin(1)==g.raEnd(1));
}