#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "Set.h"
#include <sstream>
#include <string>
#include <stdexcept>


TEST_CASE("isEmpty: empty set returns true", "[CantorSet]") {
    CantorSet s;
    REQUIRE(s.isEmpty());
}

TEST_CASE("isEmpty: with element returns false", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    REQUIRE_FALSE(s.isEmpty());
}

TEST_CASE("isEmpty: with subset returns false", "[CantorSet]") {
    CantorSet s;
    s.addSubset(CantorSet());
    REQUIRE_FALSE(s.isEmpty());
}

TEST_CASE("isEmpty: with element and subset returns false", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    s.addSubset(CantorSet());
    REQUIRE_FALSE(s.isEmpty());
}

TEST_CASE("addElement: new element", "[CantorSet]") {
    CantorSet s;
    REQUIRE(s.addElement("a"));
    REQUIRE(s["a"]);
}

TEST_CASE("addElement: duplicate returns false", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    REQUIRE_FALSE(s.addElement("a"));
}

TEST_CASE("addElement: empty string rejected", "[CantorSet]") {
    CantorSet s;
    REQUIRE_FALSE(s.addElement(""));
}

TEST_CASE("addElement: multi-character", "[CantorSet]") {
    CantorSet s;
    REQUIRE(s.addElement("abc"));
    REQUIRE(s.addElement("123"));
    REQUIRE(s.addElement("a1b2"));
}


TEST_CASE("delElement: removes existing", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    s.addElement("b");
    REQUIRE(s.delElement("a"));
    REQUIRE_FALSE(s["a"]);
    REQUIRE(s["b"]);
}

TEST_CASE("delElement: non-existing returns false", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    REQUIRE_FALSE(s.delElement("z"));
}

TEST_CASE("delElement: repeat removal fails", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    REQUIRE(s.delElement("a"));
    REQUIRE_FALSE(s.delElement("a"));
}


TEST_CASE("power: empty set is 0", "[CantorSet]") {
    CantorSet s;
    REQUIRE(s.power() == 0);
}

TEST_CASE("power: with elements", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    REQUIRE(s.power() == 1);
    s.addElement("b");
    REQUIRE(s.power() == 2);
}

TEST_CASE("power: with subsets", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    s.addSubset(CantorSet());
    REQUIRE(s.power() == 2);
}


TEST_CASE("operator[] string: present", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    s.addElement("b");
    REQUIRE(s["a"]);
    REQUIRE(s["b"]);
}

TEST_CASE("operator[] string: absent", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    REQUIRE_FALSE(s["z"]);
    REQUIRE_FALSE(s[""]);
}


TEST_CASE("operator[] CantorSet: present", "[CantorSet]") {
    CantorSet s;
    CantorSet sub;
    sub.addElement("x");
    s.addSubset(sub);
    REQUIRE(s[sub]);
}

TEST_CASE("operator[] CantorSet: absent", "[CantorSet]") {
    CantorSet s;
    CantorSet sub;
    sub.addElement("x");
    CantorSet other;
    other.addElement("y");
    s.addSubset(sub);
    REQUIRE_FALSE(s[other]);
}

TEST_CASE("operator[] CantorSet: empty subset present", "[CantorSet]") {
    CantorSet s;
    s.addSubset(CantorSet());
    REQUIRE(s[CantorSet()]);
}

TEST_CASE("operator==: both empty", "[CantorSet]") {
    CantorSet a, b;
    REQUIRE(a == b);
    REQUIRE_FALSE(a != b);
}

TEST_CASE("operator==: different elements", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x");
    b.addElement("y");
    REQUIRE(a != b);
    REQUIRE_FALSE(a == b);
}

TEST_CASE("operator==: same elements", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x");
    b.addElement("x");
    REQUIRE(a == b);
}

TEST_CASE("operator==: different count", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x");
    a.addElement("y");
    b.addElement("x");
    REQUIRE(a != b);
}

TEST_CASE("operator==: different subsets", "[CantorSet]") {
    CantorSet a, b;
    CantorSet sub1; sub1.addElement("p");
    CantorSet sub2; sub2.addElement("q");
    a.addSubset(sub1);
    b.addSubset(sub2);
    REQUIRE(a != b);
}

TEST_CASE("operator==: same subsets", "[CantorSet]") {
    CantorSet a, b;
    CantorSet sub; sub.addElement("p");
    a.addSubset(sub);
    b.addSubset(sub);
    REQUIRE(a == b);
}


TEST_CASE("addSubset: new subset", "[CantorSet]") {
    CantorSet s;
    CantorSet sub;
    sub.addElement("a");
    REQUIRE(s.addSubset(sub));
    REQUIRE(s[sub]);
}

TEST_CASE("addSubset: duplicate rejected", "[CantorSet]") {
    CantorSet s;
    CantorSet sub;
    sub.addElement("a");
    s.addSubset(sub);
    REQUIRE_FALSE(s.addSubset(sub));
}

TEST_CASE("addSubset: empty subset", "[CantorSet]") {
    CantorSet s;
    REQUIRE(s.addSubset(CantorSet()));
    REQUIRE_FALSE(s.addSubset(CantorSet()));
}

TEST_CASE("addSubset: multiple distinct subsets", "[CantorSet]") {
    CantorSet s;
    CantorSet sub1; sub1.addElement("a");
    CantorSet sub2; sub2.addElement("b");
    REQUIRE(s.addSubset(sub1));
    REQUIRE(s.addSubset(sub2));
    REQUIRE(s.power() == 2);
}


TEST_CASE("delSubset: removes existing", "[CantorSet]") {
    CantorSet s;
    CantorSet sub;
    sub.addElement("a");
    s.addSubset(sub);
    REQUIRE(s.delSubset(sub));
    REQUIRE(s.isEmpty());
}

TEST_CASE("delSubset: non-existing fails", "[CantorSet]") {
    CantorSet s;
    CantorSet sub;
    sub.addElement("a");
    CantorSet other;
    other.addElement("b");
    s.addSubset(sub);
    REQUIRE_FALSE(s.delSubset(other));
}

TEST_CASE("delSubset: repeat removal fails", "[CantorSet]") {
    CantorSet s;
    CantorSet sub;
    sub.addElement("a");
    s.addSubset(sub);
    REQUIRE(s.delSubset(sub));
    REQUIRE_FALSE(s.delSubset(sub));
}


TEST_CASE("operator<: both empty", "[CantorSet]") {
    CantorSet a, b;
    REQUIRE_FALSE(a < b);
    REQUIRE_FALSE(b < a);
}

TEST_CASE("operator<: different elements", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x");
    b.addElement("y");
    REQUIRE(a < b);
    REQUIRE_FALSE(b < a);
}

TEST_CASE("operator<: empty less than non-empty", "[CantorSet]") {
    CantorSet a, b;
    b.addElement("x");
    REQUIRE(a < b);
    REQUIRE_FALSE(b < a);
}

TEST_CASE("operator<: different subset count", "[CantorSet]") {
    CantorSet a, b;
    CantorSet sub; sub.addElement("a");
    a.addSubset(sub);
    REQUIRE(b < a);
    REQUIRE_FALSE(a < b);
}

TEST_CASE("operator<: different subsets same count", "[CantorSet]") {
    CantorSet a, b;
    CantorSet subA; subA.addElement("a");
    CantorSet subB; subB.addElement("b");
    a.addSubset(subA);
    b.addSubset(subB);
    REQUIRE(a < b);
    REQUIRE_FALSE(b < a);
}

TEST_CASE("operator<: equal returns false both ways", "[CantorSet]") {
    CantorSet a, b;
    CantorSet sub; sub.addElement("a");
    a.addSubset(sub);
    b.addSubset(sub);
    REQUIRE_FALSE(a < b);
    REQUIRE_FALSE(b < a);
}


TEST_CASE("operator+=: simple union", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x");
    b.addElement("y");
    a += b;
    REQUIRE(a["x"]);
    REQUIRE(a["y"]);
    REQUIRE(a.power() == 2);
}

TEST_CASE("operator+=: duplicates collapse", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x");
    b.addElement("x");
    b.addElement("y");
    a += b;
    REQUIRE(a.power() == 2);
}

TEST_CASE("operator+=: self-application no-op", "[CantorSet]") {
    CantorSet a;
    a.addElement("z");
    a += a;
    REQUIRE(a.power() == 1);
}

TEST_CASE("operator+=: same subsets collapse", "[CantorSet]") {
    CantorSet a, b;
    CantorSet sub; sub.addElement("a");
    a.addSubset(sub);
    b.addSubset(sub);
    a += b;
    REQUIRE(a.power() == 1);
}

TEST_CASE("operator+=: different subsets", "[CantorSet]") {
    CantorSet a, b;
    CantorSet sub1; sub1.addElement("a");
    CantorSet sub2; sub2.addElement("b");
    a.addSubset(sub1);
    b.addSubset(sub2);
    a += b;
    REQUIRE(a.power() == 2);
}


TEST_CASE("operator+: does not modify operands", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x");
    b.addElement("y");
    CantorSet c = a + b;
    REQUIRE(c["x"]);
    REQUIRE(c["y"]);
    REQUIRE(c.power() == 2);
    REQUIRE(a.power() == 1);
    REQUIRE(b.power() == 1);
}

TEST_CASE("operator+: empty operands", "[CantorSet]") {
    CantorSet a, b;
    CantorSet c = a + b;
    REQUIRE(c.isEmpty());
}

TEST_CASE("operator*=: intersection", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x"); a.addElement("y");
    b.addElement("y"); b.addElement("z");
    a *= b;
    REQUIRE(a["y"]);
    REQUIRE_FALSE(a["x"]);
    REQUIRE_FALSE(a["z"]);
    REQUIRE(a.power() == 1);
}

TEST_CASE("operator*=: self-application no-op", "[CantorSet]") {
    CantorSet a;
    a.addElement("q");
    a *= a;
    REQUIRE(a["q"]);
    REQUIRE(a.power() == 1);
}

TEST_CASE("operator*=: no common elements", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("a");
    b.addElement("b");
    a *= b;
    REQUIRE(a.isEmpty());
}

TEST_CASE("operator*=: common subset", "[CantorSet]") {
    CantorSet a, b;
    CantorSet sub; sub.addElement("a");
    a.addSubset(sub);
    b.addSubset(sub);
    a *= b;
    REQUIRE(a.power() == 1);
    REQUIRE(a[sub]);
}

TEST_CASE("operator*=: no common subsets", "[CantorSet]") {
    CantorSet a, b;
    CantorSet sub1; sub1.addElement("a");
    CantorSet sub2; sub2.addElement("b");
    a.addSubset(sub1);
    b.addSubset(sub2);
    a *= b;
    REQUIRE(a.isEmpty());
}

TEST_CASE("operator*: does not modify operands", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x"); a.addElement("y");
    b.addElement("y");
    CantorSet c = a * b;
    REQUIRE(c["y"]);
    REQUIRE(c.power() == 1);
    REQUIRE(a.power() == 2);
    REQUIRE(b.power() == 1);
}


TEST_CASE("operator-=: difference", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x"); a.addElement("y");
    b.addElement("y");
    a -= b;
    REQUIRE(a["x"]);
    REQUIRE_FALSE(a["y"]);
    REQUIRE(a.power() == 1);
}

TEST_CASE("operator-=: self-application empties", "[CantorSet]") {
    CantorSet a;
    a.addElement("q");
    a -= a;
    REQUIRE(a.isEmpty());
}

TEST_CASE("operator-=: subsets removed", "[CantorSet]") {
    CantorSet a, b;
    CantorSet sub1; sub1.addElement("a");
    CantorSet sub2; sub2.addElement("b");
    a.addSubset(sub1);
    a.addSubset(sub2);
    b.addSubset(sub1);
    a -= b;
    REQUIRE(a.power() == 1);
}

TEST_CASE("operator-=: no common elements", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("a");
    b.addElement("b");
    a -= b;
    REQUIRE(a.power() == 1);
    REQUIRE(a["a"]);
}


TEST_CASE("operator-: does not modify operands", "[CantorSet]") {
    CantorSet a, b;
    a.addElement("x"); a.addElement("y");
    b.addElement("y");
    CantorSet c = a - b;
    REQUIRE(c["x"]);
    REQUIRE_FALSE(c["y"]);
    REQUIRE(a.power() == 2);
    REQUIRE(b.power() == 1);
}


TEST_CASE("bulean: empty set gives 1 subset", "[CantorSet]") {
    CantorSet s;
    CantorSet b = s.bulean();
    REQUIRE(b.power() == 1);
    REQUIRE(b[CantorSet()]);
}

TEST_CASE("bulean: single element gives 2", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    CantorSet b = s.bulean();
    REQUIRE(b.power() == 2);
}

TEST_CASE("bulean: two elements gives 4", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    s.addElement("b");
    CantorSet b = s.bulean();
    REQUIRE(b.power() == 4);
}

TEST_CASE("bulean: three elements gives 8", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    s.addElement("b");
    s.addElement("c");
    CantorSet b = s.bulean();
    REQUIRE(b.power() == 8);
}

TEST_CASE("bulean: with subset gives 4", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    CantorSet sub; sub.addElement("x");
    s.addSubset(sub);
    CantorSet b = s.bulean();
    REQUIRE(b.power() == 4);
}

TEST_CASE("bulean: only subsets", "[CantorSet]") {
    CantorSet s;
    CantorSet sub1; sub1.addElement("p");
    CantorSet sub2; sub2.addElement("q");
    s.addSubset(sub1);
    s.addSubset(sub2);
    CantorSet b = s.bulean();
    REQUIRE(b.power() == 4);
}


TEST_CASE("operator<<: empty set", "[CantorSet]") {
    CantorSet s;
    std::ostringstream out;
    out << s;
    REQUIRE(out.str() == "{}");
}

TEST_CASE("operator<<: single element", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    std::ostringstream out;
    out << s;
    REQUIRE(out.str() == "{a}");
}

TEST_CASE("operator<<: two elements", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    s.addElement("b");
    std::ostringstream out;
    out << s;
    REQUIRE(out.str() == "{a, b}");
}

TEST_CASE("operator<<: empty subset", "[CantorSet]") {
    CantorSet s;
    s.addSubset(CantorSet());
    std::ostringstream out;
    out << s;
    REQUIRE(out.str() == "{{}}");
}

TEST_CASE("operator<<: element and subset", "[CantorSet]") {
    CantorSet s;
    s.addElement("a");
    CantorSet sub; sub.addElement("b");
    s.addSubset(sub);
    std::ostringstream out;
    out << s;
    REQUIRE(out.str() == "{a, {b}}");
}

TEST_CASE("operator>>: valid simple", "[CantorSet]") {
    std::istringstream in("{a, b}");
    CantorSet s;
    in >> s;
    REQUIRE(s["a"]);
    REQUIRE(s["b"]);
    REQUIRE(s.power() == 2);
}

TEST_CASE("operator>>: empty set", "[CantorSet]") {
    std::istringstream in("{}");
    CantorSet s;
    in >> s;
    REQUIRE(s.isEmpty());
}

TEST_CASE("operator>>: with nested subset", "[CantorSet]") {
    std::istringstream in("{a, {b, c}}");
    CantorSet s;
    in >> s;
    REQUIRE(s.power() == 2);
}

TEST_CASE("operator>>: invalid throws", "[CantorSet]") {
    std::istringstream in("{a, b");
    CantorSet s;
    REQUIRE_THROWS(s = (in >> s, s));
}

TEST_CASE("operator>>: multiple lines", "[CantorSet]") {
    std::istringstream in("{a}\n{b}");
    CantorSet s1, s2;
    in >> s1;
    in >> s2;
    REQUIRE(s1["a"]);
    REQUIRE(s2["b"]);
}


TEST_CASE("fromString: empty braces", "[CantorSet]") {
    REQUIRE(CantorSet::fromString("{}").isEmpty());
}

TEST_CASE("fromString: spaces around empty", "[CantorSet]") {
    REQUIRE(CantorSet::fromString("{ }").isEmpty());
    REQUIRE(CantorSet::fromString("  {}  ").isEmpty());
}

TEST_CASE("fromString: single atom", "[CantorSet]") {
    REQUIRE(CantorSet::fromString("{a}")["a"]);
}

TEST_CASE("fromString: without spaces", "[CantorSet]") {
    REQUIRE(CantorSet::fromString("{a,b}")["a"]);
    REQUIRE(CantorSet::fromString("{a,b}")["b"]);
}

TEST_CASE("fromString: with spaces", "[CantorSet]") {
    REQUIRE(CantorSet::fromString("{a, b}")["a"]);
    REQUIRE(CantorSet::fromString("{a, b}")["b"]);
}

TEST_CASE("fromString: nested subset", "[CantorSet]") {
    CantorSet s = CantorSet::fromString("{a, {b}}");
    REQUIRE(s.power() == 2);
}

TEST_CASE("fromString: empty subset inside", "[CantorSet]") {
    CantorSet s = CantorSet::fromString("{{}}");
    REQUIRE(s.power() == 1);
    REQUIRE(s[CantorSet()]);
}

TEST_CASE("fromString: double nesting", "[CantorSet]") {
    CantorSet s = CantorSet::fromString("{a, {b, {c}}}");
    REQUIRE(s.power() == 2);
}

TEST_CASE("fromString: multi-char atoms", "[CantorSet]") {
    REQUIRE(CantorSet::fromString("{abc123}")["abc123"]);
}

TEST_CASE("fromString: tabs and newlines", "[CantorSet]") {
    CantorSet s = CantorSet::fromString("{\ta,\n b}");
    REQUIRE(s.power() == 2);
}

TEST_CASE("fromString: task example", "[CantorSet]") {
    CantorSet s = CantorSet::fromString("{a, b, c, {a, b}, {}, {a, {c}}}");
    REQUIRE(s.power() == 6);
}

TEST_CASE("fromString: empty string throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString(""), std::runtime_error);
}

TEST_CASE("fromString: no braces throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("abc"), std::runtime_error);
}

TEST_CASE("fromString: unclosed throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{a, b"), std::runtime_error);
}

TEST_CASE("fromString: no opening throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("a, b}"), std::runtime_error);
}

TEST_CASE("fromString: trailing comma throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{a,}"), std::runtime_error);
}

TEST_CASE("fromString: leading comma throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{,a}"), std::runtime_error);
}

TEST_CASE("fromString: double comma throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{a,,b}"), std::runtime_error);
}

TEST_CASE("fromString: invalid char throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{@}"), std::runtime_error);
}

TEST_CASE("fromString: garbage after throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{a} abc"), std::runtime_error);
}

TEST_CASE("fromString: missing comma throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{a b}"), std::runtime_error);
}

TEST_CASE("fromString: nested unclosed throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{a, {b}"), std::runtime_error);
}

TEST_CASE("fromString: extra brace throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{}}"), std::runtime_error);
}

TEST_CASE("fromString: only { throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{"), std::runtime_error);
}

TEST_CASE("fromString: {a without close throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{a"), std::runtime_error);
}

TEST_CASE("fromString: space then } throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString(" }"), std::runtime_error);
}

TEST_CASE("fromString: only comma throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{,}"), std::runtime_error);
}

TEST_CASE("fromString: garbage inside throws", "[CantorSet]") {
    REQUIRE_THROWS_AS(CantorSet::fromString("{ {} @ }"), std::runtime_error);
}