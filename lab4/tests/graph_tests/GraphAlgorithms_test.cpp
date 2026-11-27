#include <catch2/catch_test_macros.hpp>
#include "Graph.hpp"

#include <sstream>
#include <stdexcept>

namespace{

using G = Graph<int>;

void fillSample(G& g){
    for(int i=1;i<=4;++i) g.addVertex(i);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,1);
    g.addEdge(3,4);
}

void fillLoop(G& g){
    g.addVertex(1);
    g.addVertex(2);
    g.addEdge(1,1);
    g.addEdge(1,2);
}

}

TEST_CASE("GraphAlgorithms: edgeDegree") {
    G g;
    fillSample(g);

    SECTION("Regular edges") {
        REQUIRE(g.edgeDegree(3,4)==2u);
        REQUIRE(g.edgeDegree(1,2)==2u);
        REQUIRE(g.edgeDegree(1,3)==3u);
        REQUIRE(g.edgeDegree(3,1)==3u);
    }

}

TEST_CASE("GraphAlgorithms: key ignores insertion order and edge direction") {
    G a;
    a.addVertex(1); a.addVertex(2); a.addVertex(3);
    a.addEdge(1,2); a.addEdge(3,2);

    G b;
    b.addVertex(3); b.addVertex(1); b.addVertex(2);
    b.addEdge(2,3); b.addEdge(2,1);

    REQUIRE(a==b);
}

TEST_CASE("GraphAlgorithms: key distinguishes graphs") {
    G a;
    a.addVertex(1); a.addVertex(2);
    a.addEdge(1,2);

    G b;
    b.addVertex(1); b.addVertex(2);

    REQUIRE(a!=b);
    REQUIRE(b<a);
}

TEST_CASE("GraphAlgorithms: stream output") {
    std::ostringstream os;

    SECTION("Empty graph") {
        G g;
        os<<g;
        REQUIRE(os.str()=="Graph{ vertices=[], edges=[] }");
    }

    SECTION("Non-empty graph") {
        G g;
        fillSample(g);
        os<<g;
        REQUIRE(os.str()=="Graph{ vertices=[1, 2, 3, 4], edges=[(1,2), (2,3), (1,3), (3,4)] }");
    }
}