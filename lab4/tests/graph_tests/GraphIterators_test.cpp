#include <catch2/catch_test_macros.hpp>
#include "Graph.hpp"

#include <stdexcept>
#include <utility>
#include <vector>

namespace{

using G = Graph<int>;
using Edge = std::pair<int,int>;
using Vertices = std::vector<int>;
using Edges = std::vector<Edge>;

void fillSample(G& g){
    for(int i=1;i<=4;++i) g.addVertex(i);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,1);
    g.addEdge(3,4);
}

template <typename It>
std::vector<typename It::value_type> collect(It first, It last){
    std::vector<typename It::value_type> result;
    for(; first!=last; ++first) result.push_back(*first);
    return result;
}

}

TEST_CASE("GraphIterators: vertex iterators") {
    G g;
    fillSample(g);
    const G& cg=g;
    const Vertices forward{1,2,3,4};
    const Vertices backward{4,3,2,1};

    SECTION("Forward") {
        REQUIRE(collect(g.vBegin(), g.vEnd())==forward);
    }
    SECTION("Reverse") {
        REQUIRE(collect(g.rvBegin(), g.rvEnd())==backward);
    }
}

TEST_CASE("GraphIterators: edge iterators") {
    G g;
    fillSample(g);
    const G& cg=g;
    const Edges forward{{1,2},{2,3},{1,3},{3,4}};
    const Edges backward{{3,4},{1,3},{2,3},{1,2}};

    SECTION("Forward") {
        REQUIRE(collect(g.eBegin(), g.eEnd())==forward);
    }
    SECTION("Reverse") {
        REQUIRE(collect(g.reBegin(), g.reEnd())==backward);
    }
    SECTION("Const forward") {
        REQUIRE(collect(cg.ceBegin(), cg.ceEnd())==forward);
    }
    SECTION("Const reverse") {
        REQUIRE(collect(cg.creBegin(), cg.creEnd())==backward);
    }
    SECTION("Endpoints are ordered inside the pair") {
        G h;
        h.addVertex(5);
        h.addVertex(2);
        h.addEdge(5,2);
        const Edge expected{2,5};
        REQUIRE(*h.eBegin()==expected);
    }
}

TEST_CASE("GraphIterators: incident edge iterators") {
    G g;
    fillSample(g);
    const G& cg=g;
    const Edges forward{{3,2},{3,1},{3,4}};
    const Edges backward{{3,4},{3,1},{3,2}};

    SECTION("Forward") {
        REQUIRE(collect(g.iBegin(3), g.iEnd(3))==forward);
    }
    SECTION("Reverse") {
        REQUIRE(collect(g.riBegin(3), g.riEnd(3))==backward);
    }
    SECTION("Const forward") {
        REQUIRE(collect(cg.ciBegin(3), cg.ciEnd(3))==forward);
    }
    SECTION("Const reverse") {
        REQUIRE(collect(cg.criBegin(3), cg.criEnd(3))==backward);
    }
    SECTION("Isolated vertex has no incident edges") {
        g.addVertex(5);
        REQUIRE(g.iBegin(5)==g.iEnd(5));
        REQUIRE(g.riBegin(5)==g.riEnd(5));
    }
   
}

TEST_CASE("GraphIterators: adjacent vertex iterators") {
    G g;
    fillSample(g);
    const G& cg=g;
    const Vertices forward{2,1,4};
    const Vertices backward{4,1,2};

    SECTION("Forward") {
        REQUIRE(collect(g.aBegin(3), g.aEnd(3))==forward);
    }
    SECTION("Reverse") {
        REQUIRE(collect(g.raBegin(3), g.raEnd(3))==backward);
    }
    SECTION("Const forward") {
        REQUIRE(collect(cg.caBegin(3), cg.caEnd(3))==forward);
    }
    SECTION("Const reverse") {
        REQUIRE(collect(cg.craBegin(3), cg.craEnd(3))==backward);
    }
}

TEST_CASE("GraphIterators: increment, decrement and comparison") {
    G g;
    fillSample(g);

    SECTION("Prefix and postfix on a forward iterator") {
        auto it=g.vBegin();
        auto old=it++;
        REQUIRE(*old==1);
        REQUIRE(*it==2);
        ++it;
        REQUIRE(*it==3);
        auto older=it--;
        REQUIRE(*older==3);
        REQUIRE(*it==2);
        --it;
        REQUIRE(it==g.vBegin());
        REQUIRE(it!=g.vEnd());
    }

    SECTION("Decrement from end") {
        auto it=g.vEnd();
        --it;
        REQUIRE(*it==4);
    }

    SECTION("Prefix and postfix on a reverse iterator") {
        auto it=g.rvBegin();
        REQUIRE(*it==4);
        auto old=it++;
        REQUIRE(*old==4);
        REQUIRE(*it==3);
        ++it;
        --it;
        REQUIRE(*it==3);
        auto older=it--;
        REQUIRE(*older==3);
        REQUIRE(it==g.rvBegin());
    }


    SECTION("Postfix on adjacent iterator") {
        auto a=g.aBegin(3);
        auto old=a++;
        REQUIRE(*old==2);
        REQUIRE(*a==1);
    }

    SECTION("Iterators of different vertices are not equal") {
        REQUIRE(g.iBegin(1)!=g.iBegin(2));
    }

}

TEST_CASE("GraphIterators: conversion to const iterator") {
    G g;
    fillSample(g);

    G::ConstVertexIterator cv=g.vBegin();
    REQUIRE(*cv==1);

    G::ConstIncidentIterator ci=g.iBegin(3);
    REQUIRE(ci==g.ciBegin(3));
}