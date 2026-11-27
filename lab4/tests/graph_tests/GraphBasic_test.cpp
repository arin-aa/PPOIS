#include <catch2/catch_test_macros.hpp>
#include "Graph.hpp"

#include <stdexcept>
#include <utility>

namespace{

using G = Graph<int>;
using Edge = std::pair<int,int>;

void fillSample(G& g){
    for(int i=1;i<=4;++i) g.addVertex(i);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,1);
    g.addEdge(3,4);
}

}

TEST_CASE("GraphBasic: empty graph") {
    G g;
    REQUIRE(g.empty());
    REQUIRE(g.vertexCount()==0u);
    REQUIRE(g.edgeCount()==0u);
}

TEST_CASE("GraphBasic: addVertex") {
    G g;

    SECTION("Returns iterator to the new vertex") {
        auto it=g.addVertex(7);
        REQUIRE(*it==7);
        REQUIRE(g.vertexCount()==1u);
        REQUIRE_FALSE(g.empty());
    }

    SECTION("Duplicate vertex is rejected") {
        g.addVertex(1);
        REQUIRE_THROWS_AS(g.addVertex(1), std::invalid_argument);
        REQUIRE(g.vertexCount()==1u);
    }
}

TEST_CASE("GraphBasic: addEdge") {
    G g;
    g.addVertex(1);
    g.addVertex(2);

    SECTION("Adds an edge") {
        g.addEdge(1,2);
        REQUIRE(g.edgeCount()==1u);
        REQUIRE(g.containsEdge(1,2));
    }

    SECTION("Parallel edge is rejected in both directions") {
        g.addEdge(1,2);
        REQUIRE_THROWS_AS(g.addEdge(1,2), std::invalid_argument);
        REQUIRE_THROWS_AS(g.addEdge(2,1), std::invalid_argument);
        REQUIRE(g.edgeCount()==1u);
    }

}

TEST_CASE("GraphBasic: containsVertex and containsEdge") {
    G g;
    fillSample(g);
    const G& cg=g;

    SECTION("Vertices") {
        REQUIRE(cg.containsVertex(3));
        REQUIRE_FALSE(cg.containsVertex(42));
    }

    SECTION("Edges are undirected") {
        REQUIRE(cg.containsEdge(1,2));
        REQUIRE(cg.containsEdge(2,1));
        REQUIRE_FALSE(cg.containsEdge(1,4));
    }

    SECTION("Edge with a missing vertex is simply absent") {
        REQUIRE_FALSE(cg.containsEdge(1,42));
        REQUIRE_FALSE(cg.containsEdge(42,1));
    }
}

TEST_CASE("GraphBasic: degree") {
    G g;
    fillSample(g);

    SECTION("Regular vertices") {
        REQUIRE(g.degree(1)==2u);
        REQUIRE(g.degree(2)==2u);
        REQUIRE(g.degree(3)==3u);
        REQUIRE(g.degree(4)==1u);
    }

    SECTION("Missing vertex") {
        REQUIRE_THROWS_AS(g.degree(42), std::out_of_range);
    }
}

TEST_CASE("GraphBasic: removeVertex") {
    G g;
    fillSample(g);

    SECTION("Removes the vertex and its edges") {
        g.removeVertex(3);
        REQUIRE_FALSE(g.containsVertex(3));
        REQUIRE(g.vertexCount()==3u);
        REQUIRE(g.edgeCount()==1u);
        REQUIRE(g.containsEdge(1,2));
        REQUIRE(g.degree(1)==1u);
        REQUIRE(g.degree(2)==1u);
        REQUIRE(g.degree(4)==0u);
    }

    SECTION("Missing vertex") {
        REQUIRE_THROWS_AS(g.removeVertex(42), std::out_of_range);
    }
}

TEST_CASE("GraphBasic: removeEdge") {
    G g;
    fillSample(g);

    SECTION("Removes the edge in either direction") {
        g.removeEdge(2,1);
        REQUIRE_FALSE(g.containsEdge(1,2));
        REQUIRE(g.edgeCount()==3u);
        REQUIRE(g.degree(1)==1u);
        REQUIRE(g.degree(2)==1u);
        REQUIRE(g.vertexCount()==4u);
    }

    SECTION("Removes a loop") {
        g.addEdge(4,4);
        g.removeEdge(4,4);
        REQUIRE_FALSE(g.containsEdge(4,4));
        REQUIRE(g.degree(4)==1u);
    }

    SECTION("Missing vertex") {
        REQUIRE_THROWS_AS(g.removeEdge(42,1), std::out_of_range);
        REQUIRE_THROWS_AS(g.removeEdge(1,42), std::out_of_range);
    }

    SECTION("Missing edge") {
        REQUIRE_THROWS_AS(g.removeEdge(1,4), std::invalid_argument);
    }
}

TEST_CASE("GraphBasic: eraseVertex by iterator") {
    G g;
    fillSample(g);

    SECTION("Middle vertex") {
        auto it=g.vBegin();
        ++it;
        auto next=g.eraseVertex(it);
        REQUIRE(*next==3);
        REQUIRE_FALSE(g.containsVertex(2));
        REQUIRE(g.vertexCount()==3u);
        REQUIRE(g.edgeCount()==2u);
        REQUIRE(g.degree(1)==1u);
        REQUIRE(g.degree(3)==2u);
    }

    SECTION("Last vertex returns end") {
        auto it=g.vEnd();
        --it;
        auto next=g.eraseVertex(it);
        REQUIRE(next==g.vEnd());
        REQUIRE(g.edgeCount()==3u);
        REQUIRE(g.degree(3)==2u);
    }

}

TEST_CASE("GraphBasic: eraseEdge by iterator") {
    G g;
    fillSample(g);

    SECTION("Last edge returns end") {
        auto it=g.eEnd();
        --it;
        auto next=g.eraseEdge(it);
        REQUIRE(next==g.eEnd());
        REQUIRE(g.degree(4)==0u);
    }

    SECTION("Loop") {
        G h;
        h.addVertex(1);
        h.addEdge(1,1);
        h.eraseEdge(h.eBegin());
        REQUIRE(h.edgeCount()==0u);
        REQUIRE(h.degree(1)==0u);
    }
}

TEST_CASE("GraphBasic: copy constructor and assignment") {
    G g;
    fillSample(g);
    g.addVertex(5);
    g.addEdge(5,5);

    SECTION("Copy is equal and independent") {
        G copy(g);
        REQUIRE(copy==g);
        REQUIRE(copy.edgeCount()==g.edgeCount());

        copy.addVertex(100);
        copy.removeVertex(1);
        REQUIRE_FALSE(g.containsVertex(100));
        REQUIRE(g.containsVertex(1));
        REQUIRE(g.containsEdge(1,2));
        REQUIRE(copy!=g);
    }

}

TEST_CASE("GraphBasic: clear") {
    G g;
    fillSample(g);
    g.clear();
    REQUIRE(g.empty());
    REQUIRE(g.vertexCount()==0u);
    REQUIRE(g.edgeCount()==0u);

    g.addVertex(1);
    REQUIRE(g.vertexCount()==1u);
}